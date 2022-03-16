/**************************************************************************
 ** Dynamic Networking Solutions                                         **
 **************************************************************************
 ** OpenAPRS, Internet APRS MySQL Injector                               **
 ** Copyright (C) 1999 Gregory A. Carter                                 **
 **                    Dynamic Networking Solutions                      **
 **                                                                      **
 ** This program is free software; you can redistribute it and/or modify **
 ** it under the terms of the GNU General Public License as published by **
 ** the Free Software Foundation; either version 1, or (at your option)  **
 ** any later version.                                                   **
 **                                                                      **
 ** This program is distributed in the hope that it will be useful,      **
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of       **
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        **
 ** GNU General Public License for more details.                         **
 **                                                                      **
 ** You should have received a copy of the GNU General Public License    **
 ** along with this program; if not, write to the Free Software          **
 ** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            **
 **************************************************************************
 $Id: APRS.cpp,v 1.2 2005/12/13 21:07:03 omni Exp $
 **************************************************************************/

#include <list>
#include <new>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <openframe/openframe.h>

#include "Convert.h"
#include "Position.h"
#include "APRS_Exception.h"

namespace aprs {

/**************************************************************************
 ** Packet Class                                                         **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/
  const char *Position::kCommandChar		= "=";
  const char *Position::kCommandCharCompressed	= "!";

  Position::Position(const std::string &source, const std::string &dest,
                     const double latitude, const double longitude,
                     const char symbol_table, const char symbol_code,
                     const int course, const double speed,
                     const double altitude, const int ambiguity,
                     const std::string comment)
           : super(source, dest),
             _latitude(latitude),
             _longitude(longitude),
             _symbol_table(symbol_table),
             _symbol_code(symbol_code),
             _course(course),
             _speed(speed),
             _altitude(altitude),
             _ambiguity(ambiguity),
             _comment(comment) {

    bool ok = latitude < -89.99999
              || latitude > 89.99999
              || longitude < -179.99999
              || longitude > 179.99999;
    if (ok) throw APRS_Exception("invalid latitude or longitude");

    // check for valid symbol table
    ok = (symbol_table >= 33 && symbol_table <= 123)
         || symbol_table == 125;
    if (!ok) throw APRS_Exception("invalid symbol table");

  } // Position::Position

  Position::~Position() {
  } // Position::~Position

  std::string Position::compile() const {
    std::stringstream ret;
    ret << header()
        << command_char()
        << compile_position();
    return ret.str();
  } // Position::compile

  std::string Position::compile_position() const {
    // passed checks, initialize variables
    std::stringstream lats;
    std::stringstream longs;
    double latval = _latitude;
    double longval = _longitude;

    // uncompressed format
    bool isNorth = true;

    if (_latitude < 0) {
      latval = 0 - _latitude;
      isNorth = false;
    } // if

    std::map<std::string, int> deg;
    std::map<std::string, int> min;

    deg["lat"] = int(latval);
    min["lat"] = int((latval - deg["lat"]) * 6000);
    char y[10];
    snprintf(y, sizeof(y), "%04d", min["lat"]);
    std::string t = y;
    snprintf(y, sizeof(y), "%02d%s.%s", deg["lat"], t.substr(0, 2).c_str(),
                                          t.substr(2, 2).c_str());

    t = y;
    switch(_ambiguity) {
      case 4:
        t = t.substr(0, 2) + "  .  ";
        break;
      case 3:
        t = t.substr(0, 3) + " .  ";
        break;
      case 2:
        t = t.substr(0, 4) + ".  ";
        break;
      case 1:
        t = t.substr(0, 5) + "  ";
        break;
    } // switch

    if (isNorth)
      t += "N";
    else
      t += "S";

    lats << t;

    // now process longitude
    bool isEast = true;

    if (_longitude < 0) {
      longval = 0 - _longitude;
      isEast = false;
    } // if

    deg["long"] = int(longval);
    min["long"] = int((longval - deg["long"]) * 6000);
    snprintf(y, sizeof(y), "%04d", min["long"]);
    t = y;
    snprintf(y, sizeof(y), "%03d%s.%s", deg["long"], t.substr(0, 2).c_str(),
                                        t.substr(2, 2).c_str());

    t = y;
    switch(_ambiguity) {
      case 4:
        t = t.substr(0, 3) + "  .  ";
        break;
      case 3:
        t = t.substr(0, 4) + " .  ";
        break;
      case 2:
        t = t.substr(0, 5) + ".  ";
        break;
      case 1:
        t = t.substr(0, 6) + "  ";
        break;
    } // switch

    if (isEast)
      t += "E";
    else
      t += "W";

    longs << t;

    std::stringstream ret;
    ret << lats.str()
        << _symbol_table
        << longs.str()
        << _symbol_code;

    // add course/speed
    if (_speed >= 0 && _course >= 0) {
      //convert speed to knots
      int val = KphToKnot(_speed);
      if (val > 999) val = 999;

      snprintf(y, sizeof(y), "%03d/%03d", ((_course > 360) ? 0 : _course),
                                          val);

      ret << y;
    } // if

    ret << comment();

    return ret.str();
  } // Position::compile_position

  std::string Position::compile_compressed() const {
    std::stringstream lats, longs;
    double latval = 380926 * (90 - _latitude);
    double longval = 190463 * (180 + _longitude);

    for(int i=3; i >= 0; i--) {
      // create latitude characters
      int val = int(latval / pow(91, i));
      latval = int(latval) % int(pow(91, i));
      lats << char(val + 33);

      // create longitude characters
      val = int(longval / pow(91, i));
      longval = int(longval) % int(pow(91, i));
      longs << char(val + 33);
    } // for

    // convert symbol table from 0-9 to a-z
    char symbol_table = _symbol_table;
    if (_symbol_table >= '0' && symbol_table <= '9')
      symbol_table = symbol_table + 49;

    std::stringstream ret;
    ret << header()
        << kCommandCharCompressed
        << symbol_table
        << lats.str()
        << longs.str()
        << _symbol_code;

    // encode our speed, course and altitude
    if (_speed >= 0 && _course > 0 && _course <= 360) {
      // In APRS spec unknown course is zero normally (and north is 360),
      // but in compressed aprs north is zero and there is no unknown course.
      // So round course to nearest 4-degree section and remember
      // to do the 360 -> 0 degree transformation.
      int val = (_course + 2) / 4;
      if (val > 89) val = 0;

      ret << char(val + 33);

      // speed is in knots in compressed form, round to nearest integer
      //val = int(log(oSpeed + 1.0) / log(1.08) + 0.5);
      val = int(log(_speed + 1.0) / log(1.08) + 0.5);
      if (val > 89)
        // limit top speed
        val = 89;

      ret << char(val + 33) << std::string("A");
    } // if
    else
      ret << "  A";

    ret << comment();

    return ret.str();
  } // Position::compile_compressed
} // namespace aprs
