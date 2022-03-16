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

#include <openframe/openframe.h>

#include "UnitTest.h"

int main(int argc, char **argv) {
  aprs::UnitTest ut;

  ut.run();

  return 0;
} // main
