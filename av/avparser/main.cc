#include "FlvParser.h"
#include <time.h>

using namespace AV;

int main(int argc, const char** argv) {
  clock_t start = clock();
  FlvParser parser(argv[1]);
  auto res = parser.Parse();

    clock_t end = clock();
  ::printf("time usage : %lf\n", (double(end-start)) / CLOCKS_PER_SEC);

}
