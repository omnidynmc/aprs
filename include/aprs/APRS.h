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

#ifndef LIBAPRS_APRS_H
#define LIBAPRS_APRS_H

#include <string>
#include <sstream>
#include <map>
#include <exception>

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <openframe/openframe.h>

#include "UnitTest.h"

namespace aprs {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

class APRS : public openframe::StringTool {
  public:
    APRS(const std::string &, const time_t);		// constructor
    virtual ~APRS();				// destructor

    // ### Type Definitions ###
    enum aprsPacketType {
      APRS_PACKET_POSITION		 	= 0,
      APRS_PACKET_MESSAGE 			= 1,
      APRS_PACKET_TELEMETRY			= 2,
      APRS_PACKET_STATUS			= 3,
      APRS_PACKET_CAPABILITIES			= 4,
      APRS_PACKET_WEATHER			= 5,
      APRS_PACKET_DX				= 6,
      APRS_PACKET_ITEM				= 7,
      APRS_PACKET_EXPERIMENTAL			= 8,
      APRS_PACKET_MAIDENHEAD			= 9,
      APRS_PACKET_PEETLOGGING			= 10,
      APRS_PACKET_BEACON			= 11,
      APRS_PACKET_UNKNOWN			= 254
    };

    typedef std::deque<std::string> locator_list_t;
    typedef locator_list_t::iterator locator_list_itr;
    typedef locator_list_t::const_iterator locator_list_citr;
    typedef locator_list_t::size_type locator_list_st;

    // ### Members ###
    static const bool isValidLatLong(const double, const double);
    static const bool isValidMessage(const std::string &);
    static const bool isValidCallsign(const std::string &);
    static const std::string extractCallsign(const std::string &callsign) { return _extractCallsign(callsign); }
    static const bool calcDestPoint(const int, const double, const double, const double,
                              double &, double &);
    static const double calcDistance(double, double, double, double, char);
    static const double calcSpeed(const double, const time_t,
                               const int, const int);
    static double deg2rad(double);
    static double rad2deg(double);
    static std::string create_timestamp(const time_t when, const bool zulu);

    const double latitude() const { return _latitude; }
    const double longitude() const { return _longitude; }
    const double lat() const { return _latitude; }
    const double lng() const { return _longitude; }
    const char command() const { return _command; }
    bool is_object() const { return _object; }
    const std::string source() const { return _source; }
    const std::string path() const { return _path; }
    const std::string status() const { return _status; }
    const std::string packet() const { return _packet; }
    const std::string body() const { return _body; }
    const time_t timestamp() const { return _timestamp; }
    const std::string id() const { return _id; }
    const bool position() const { return _position; }
    void position(const bool position) { _position = position; }
    const aprsPacketType packetType() const { return _packetType; }
    const bool parse() { return _parse(); }

    inline const char symbolTable() const { return _symbolTable; }
    inline const char symbolCode() const { return _symbolCode; }
    // ### Variables ###

    static char *maidenhead(double n, double e);
    size_t locator_list(const double s_lat, const double s_lng, const double e_lat, const double e_lng,
                        locator_list_t &ret);

    std::string locator_list_for_sql(const double s_lat, const double s_lng, const double e_lat, const double e_lng);

  protected:
    // ### Members ###
    const std::string _create_uuid();
    const bool _parse();
    const bool _parsePosition(const std::string &);
    const bool _parseMessage(const std::string &);
    const bool _parseNmea(const std::string &);
    const bool _parseTelemetry(const std::string &);
    const bool _parseMIC_E(const std::string &);
    const bool _parseStatus(const std::string &);
    const bool _parseCapabilities(const std::string &);
    const bool _parseExperimental(const std::string &);
    const bool _parsePeetLogging(const std::string &);
    const bool _parseBeacon(const std::string &);

    const bool _parseUltimeter(string &);
    const bool _parseWeather(string &);
    const bool _parseMessageTelemetry(string &);

    const bool _convertPos(const std::string &, const std::string &, const std::string &, const std::string &,
                           map<string, string> &);
    const bool _convertMIC_EToDecimal(string &);

    const bool _extractTimestamp(string &);
    const bool _extractWeatherTimestamp(string &);
    const bool _extractTelemetry(string &);
    const bool _extractNmea(string &);
    const bool _extractLocation(string &);
    const bool _extractLocationCompressed(string &);
    const bool _extractAltitude(string &);
    const bool _extractAltitudeHelper(string &, const std::string::size_type offset);
    const bool _extractDfs(string &);
    const bool _extractDfsHelper(string &, const std::string::size_type offset);
    const bool _extractAfrs(string &);
    const bool _extractAreaObject(string &);
    const bool _extractDfr(string &);
    const bool _extractDfrHelper(string &, const std::string::size_type offset);
    const bool _extractDirSpd(string &);
    const bool _extractWindDirSpd(string &);
    const bool _extractGustTemp(string &);
    const bool _extractRng(string &);
    const bool _extractAltSymbol(string &);
    const bool _extractSignpost(string &);
    const bool _extractPhg(string &);
    const bool _extractItem(string &);
    const bool _extractDao(string &, float &, float &);
    static const std::string _extractCallsign(const std::string &);

    const std::string _cleanupComment(const std::string &);
    const std::string _makeBufferSafe(const std::string &);

    bool _symbol(const char symbolTable, const char symbolCode);

    bool _symbol(const std::string symbolTable, const std::string symbolCode) {
      assert(symbolTable.length() || symbolCode.length());	// bug

      return _symbol(symbolTable[0], symbolCode[0]);
    } // _symbol

    void status(const std::string &status) {
      _status = status;
      replaceString("aprs.packet.comment", status);
    } // status

    // ### Members ###
    void _latlng(const double, const double);

    void _latlng(const std::string &lat, const std::string &lng) {
      _position = true;

      _latitude = atof(lat.c_str());
      _longitude = atof(lng.c_str());

      addString("aprs.packet.position.latitude.decimal", lat);
      addString("aprs.packet.position.longitude.decimal", lng);
    } // _latlng

  private:
    // ### Variables ###
    bool _position;			// has position data
    bool _telemetry;			// has telemtry data
    bool _weather;			// has weather data
    char _command;			// command
    char _symbolTable;			// symbol table
    char _symbolCode;			// symbol code
    std::string _packet;			// full packet string
    std::string _path;
    std::string _source;			// source of packet
    std::string _status;			// status report
    std::string _body;			// info portion of packet
    std::string _id;				// unique md5 id
    std::string _error;			// error message for throw
    double _latitude;			// latitude
    double _longitude;			// longitude
    bool _object;
    aprsPacketType _packetType;		// type of aprs packet
    time_t _timestamp;			// timestamp
};

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

int axtoi(const char *);

}
#endif
