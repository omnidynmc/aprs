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

#ifndef LIBAPRS_PACKET_H
#define LIBAPRS_PACKET_H

#include <deque>
#include <string>

#include <openframe/openframe.h>

namespace aprs {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class Packet {
    public:
      static const char *kSourceDestSep;
      static const char *kDigiCommandSep;

      Packet(const std::string &source, const std::string &dest);
      virtual ~Packet();

      // Type Definitions //
      typedef std::deque<std::string> digis_t;
      typedef digis_t::iterator digis_itr;
      typedef digis_t::const_iterator digis_citr;
      typedef digis_t::size_type digis_st;

      Packet &add_digi(const std::string &name);
      Packet &add_digis(const std::string &digis);
      std::string digi_list() const;

      std::string header() const;

      // Public Getters //
      inline std::string source() const { return _source; }
      inline std::string dest() const { return _dest; }
      inline time_t created_at() const { return _created_at; }

      // Pure Virtuals //
      virtual const char *command_char() const = 0;
      virtual std::string compile() const = 0;

    protected:
      inline void set_dest(const std::string &set_to) { _dest = set_to; }
    private:
      // contructor variables
      std::string _source;
      std::string _dest;
      time_t _created_at;

      digis_t _digis;
  }; // class Packet

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprs
#endif
