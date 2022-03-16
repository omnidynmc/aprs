#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>
#include <list>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <openframe/openframe.h>

#include "aprs.h"

bool parse(const std::string &line) {
  aprs::APRS *a;

  try {
    a = new aprs::APRS(line, time(NULL));
  } // try
  catch(aprs::APRS_Exception &e) {
    std::cout << " not ok - failed to parse: " << e.message() << std::endl;
    return false;
  } // catch

  STRINGTOOL_DEBUG_STRINGS(a, stringList, "root");
  while(!stringList.empty()) {
    std::cout << stringList.front() << std::endl;
    stringList.pop_front();
  } // while

  return true;
} // parse

int main(int argc, char **argv) {
  std::string line;
  while(std::getline(std::cin, line)) {
    parse(line);
    break;
  } // while
  return 0;
} // main
