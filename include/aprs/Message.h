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

#ifndef LIBAPRS_MESSAGE_H
#define LIBAPRS_MESSAGE_H

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

  class Message : public Packet {
    public:
      typedef Packet super;
      static const char *kCommandChar;

      Message(const std::string &source, const std::string &dest,
              const std::string &to,
              const std::string &body);
      virtual ~Message();

      // Public Getters //
      inline std::string to() const { return _to; }
      inline std::string body() const { return _body; }

      bool encodeMessageID(const unsigned int id, std::string &ret);

      // Pure Virtuals //
      virtual const char *command_char() const { return kCommandChar; }
      virtual std::string compile() const;

    protected:
    private:
      // contructor variables
      std::string _to;
      std::string _body;
  }; // class Message

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprs
#endif
