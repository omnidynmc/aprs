#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#include <openframe/openframe.h>

#include "aprs.h"

int main(int argc, char **argv) {

  std::cout << aprs::APRS::maidenhead(0, 0) << std::endl;

  double s_lat = 38.37719;
  double s_lng = -122.46048;

  double e_lat = 38.23926;
  double e_lng = -122.14119;

  // each field
  // lat is 18 zones of 10 degrees each
  // lng is 18 zones of 20 degrees each

  // each square
  // lat is 10 zones 1 degree each
  // lng is 10 2 degrees each
  // 100 zones total

  // decimals in square lng 0.0833333333
  // decimals in square lat 0.0416666666
  const double lat_multi = 0.0416666666;
  const double lng_multi = 0.0833333333;

  // first calc the top box start
  double top_lat = floor(s_lat / lat_multi) *lat_multi;
  double top_lng = floor(s_lng / lng_multi) *lng_multi;

  std::cout << "INPUT START: " << s_lat << "," << s_lng << std::endl;
  std::cout << "NORMALIZED START: " << top_lat << "," << top_lng << std::endl;

  std::stringstream s;
  int num = 0;
  for(double y = top_lat; y >= e_lat; y -= lat_multi) {
    for(double x = top_lng; x <= e_lng; x += lng_multi) {
      std::string loc = aprs::APRS::maidenhead(y, x);
      std::cout << y << "," << x << " " << loc << std::endl;

      s << (num ? "," : "") << "'" << loc << "'";
      ++num;
    } // for
  } // for

  std::cout << "IN (" << s.str() << ")" << std::endl;

  return 0;
} // main
