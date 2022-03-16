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

#ifndef LIBAPRS_CONVERT_H
#define LIBAPRS_CONVERT_H

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

namespace aprs {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

#define KnotToKmh(x)			(x * 1.852)
#define KphToKnot(x)			(x * 0.539956803)
#define	MphToKmh(x)			(x * 1.609344)
#define KmhToMs(x)			(x * 10 / 36)
#define MphToMs(x)			(x * 1.609344 * 10 / 36)
#define HInchToMm(x)			(x * 0.254)
#define FtToM(x)			(x * 0.3048);

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprs
#endif
