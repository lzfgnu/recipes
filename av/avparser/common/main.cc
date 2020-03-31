#include "FlvParser.h"
#include <cassert>
#include <iostream>
using namespace AV;
int main(int argc, const char** argv) {
  FlvParser parser;
  auto res = parser.Parse(argv[1]);
  ::printf("%d\n", res == AVResult::OK);
  assert(res == AVResult::OK);
}
