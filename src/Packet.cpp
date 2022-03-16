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
#include <unistd.h>

#include <openframe/openframe.h>

#include "APRS_Exception.h"
#include "Packet.h"

namespace aprs {

/**************************************************************************
 ** Packet Class                                                         **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/
  const char *Packet::kSourceDestSep		= ">";
  const char *Packet::kDigiCommandSep		= ":";

  Packet::Packet(const std::string &source, const std::string &dest)
         : _source(source),
           _dest(dest),
           _created_at( time(NULL) ) {
  } // Packet::Packet

  Packet::~Packet() {
  } // Packet::~Packet

  Packet &Packet::add_digi(const std::string &name) {
    if (_digis.size() > 7) throw APRS_Exception("too many digis");
    _digis.push_back(name);
    return *this;
  } // Packet::add_digi

  Packet &Packet::add_digis(const std::string &digis) {
    openframe::StringToken st;
    st.setDelimiter(',');
    st = digis;
    if (!st.size()) throw APRS_Exception("invalid digilist");
    if (st.size() > 7) throw APRS_Exception("too many digis");

    for(size_t i=0; i < st.size(); i++) {
      add_digi(st[i]);
    } // for
    return *this;
  } // Packet::add_digis

  std::string Packet::digi_list() const {
    std::stringstream s;
    for(digis_citr citr=_digis.begin(); citr != _digis.end(); citr++) {
      if (citr != _digis.begin()) s << ",";
      s << (*citr);
    } // for
    return s.str();
  } // Packet::digi_list

  std::string Packet::header() const {
    if (!_digis.size()) throw APRS_Exception("invalid digilist");

    std::stringstream ret;
    ret << source()
        << kSourceDestSep
        << dest()
        << ","
        << digi_list()
        << kDigiCommandSep;

    return ret.str();
  } // Packet::header
} // namespace aprs
