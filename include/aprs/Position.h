/**************************************************************************
 ** Dynamic Networking Solutions                                         **
 **************************************************************************
 ** OpenAPRS, Internet APRS MySQL Injector                               **
 ** Copyright (C) 1999 Gregory A. Carter                                 **
 **                    Daniel Robert Karrels                             **
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
 $Id: APRS.h,v 1.1 2005/11/21 18:16:02 omni Exp $
 **************************************************************************/

#ifndef LIBAPRS_POSITION_H
#define LIBAPRS_POSITION_H

#include <string>

#include <openframe/openframe.h>

#include "Packet.h"

namespace aprs {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class Position : public Packet {
    public:
      typedef Packet super;
      static const char *kCommandChar;
      static const char *kCommandCharCompressed;

      Position(const std::string &source, const std::string &dest,
               const double latitude, const double longitude,
               const char symbol_table, const char symbol_code,
               const int course, const double speed,
               const double altitude, const int ambiguity,
               const std::string comment);
      virtual ~Position();

      // Public Getters //
      inline double latitude() const { return _latitude; }
      inline double longitude() const { return _longitude; }
      inline char symbol_table() const { return _symbol_table; }
      inline char symbol_code() const { return _symbol_code; }
      inline double altitude() const { return _altitude; }
      inline int ambiguity() const { return _ambiguity; }
      inline std::string comment() const { return _comment; }

      // Pure Virtuals //
      virtual const char *command_char() const { return kCommandChar; }
      virtual std::string compile() const;
      virtual std::string compile_position() const;
      virtual std::string compile_compressed() const;

    protected:
    private:
      // contructor variables
      double _latitude;
      double _longitude;
      char _symbol_table;
      char _symbol_code;
      int _course;
      double _speed;
      double _altitude;
      int _ambiguity;
      std::string _comment;
  }; // class Position

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprs
#endif
