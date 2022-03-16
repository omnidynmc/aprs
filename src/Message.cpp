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
#include "Message.h"
#include "APRS_Exception.h"
#include "APRS.h"

namespace aprs {

/**************************************************************************
 ** Packet Class                                                         **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/
  const char *Message::kCommandChar		= ":";

  Message::Message(const std::string &source, const std::string &dest,
                   const std::string &to,
                   const std::string &body)
           : super(source, dest),
             _to(to),
             _body(body) {

    openframe::StringTool::regexMatchListType rl;
    // check for invalid target
    if (openframe::StringTool::ereg("^([A-Z0-9-]{1,9})$", to, rl) < 1)
      throw APRS_Exception("invalid to");

    bool ok = aprs::APRS::isValidMessage(body);
    if (!ok) throw APRS_Exception("invalid message body");
  } // Message::Message

  Message::~Message() {
  } // Message::~Message

  std::string Message::compile() const {
    std::stringstream ret;

    std::string pad_to = _to;
    while(pad_to.length() < 9)
      pad_to += " ";

    ret << header()
        << command_char()
        << pad_to
        << ":"
        << _body;

    return ret.str();
  } // Message::compile

  bool Message::encodeMessageID(const unsigned int id, std::string &ret) {
    static char charTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\0";
    unsigned int min, max;
    int delta;
    int first, second;
    unsigned int size;
    std::stringstream s;

    // initializev ariables
    ret = "";
    min = 0;
    max = 1295;
    delta = max - min;
    size = sizeof(charTable);

    if (id > max || id < min) return false;

    s.str("");

    first = floor(id / (size-2));
    second = id % 36;
    s << charTable[first] << charTable[second];

    ret = s.str();

    return true;
  } // Message::encodeMessageID
} // namespace aprs
