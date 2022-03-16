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

#ifndef LIBAPRS_OBJECT_H
#define LIBAPRS_OBJECT_H

#include <string>

#include <openframe/openframe.h>

#include "Position.h"

namespace aprs {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class Object : public Position {
    public:
      typedef Position super;
      static const char *kCommandChar;

      Object(const std::string &source, const std::string &name, const std::string &dest,
               const double latitude, const double longitude,
               const char symbol_table, const char symbol_code,
               const int course, const double speed,
               const double altitude, const int ambiguity,
               const std::string comment,
               const bool to_kill,
               const time_t timestamp);
      virtual ~Object();

      // Public Getters //
      inline bool to_kill() const { return _to_kill; }
      inline time_t timestamp() const { return _timestamp; }

      // Pure Virtuals //
      virtual const char *command_char() const { return kCommandChar; }
      virtual std::string compile() const;

    protected:
    private:
      // contructor variables
      std::string _name;
      bool _to_kill;
      time_t _timestamp;
  }; // class Object

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprs
#endif
