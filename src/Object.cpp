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

#include "APRS.h"
#include "APRS_Exception.h"
#include "Convert.h"
#include "Object.h"

namespace aprs {

/**************************************************************************
 ** Packet Class                                                         **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/
  const char *Object::kCommandChar		= ";";

  Object::Object(const std::string &source,
                 const std::string &dest,
                 const std::string &name,
                 const double latitude, const double longitude,
                 const char symbol_table, const char symbol_code,
                 const int course, const double speed,
                 const double altitude, const int ambiguity,
                 const std::string comment,
                 const bool to_kill,
                 const time_t timestamp)
         : super(source, dest, latitude, longitude, symbol_table, symbol_code,
                 course, speed, altitude, ambiguity, comment),
           _name(name),
           _to_kill(to_kill),
           _timestamp(timestamp) {

    openframe::StringTool::regexMatchListType rl;
    bool ok = openframe::StringTool::ereg("^([\x20-\x7e]{1,9})$", name, rl);
    if (!ok) throw APRS_Exception("invalid object name");
  } // Object::Object

  Object::~Object() {
  } // Object::~Object

  std::string Object::compile() const {
    std::stringstream ret;
    ret << header()
        << command_char();

    std::string name = _name;
    while(name.length() < 9) name += " ";

    ret << name << (!to_kill() ? "*" : "_");

    // add our timestamp
    // For some reason aprs.fi is hosing our packets with timestamps.
    ret << aprs::APRS::create_timestamp(timestamp(), true)
        << compile_position();

    return ret.str();
  } // Object::compile
} // namespace aprs
