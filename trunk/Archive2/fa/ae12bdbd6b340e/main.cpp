// search algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::search
#include <cstdint>      

using namespace std;

int main () {
  unsigned char haystack[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0xBE, 0xBD, 0x03, 0x04, 0x05};

  // using default comparison:
  uint8_t needle1[] = {0xBE, 0xBD, 0x03, 0x04};

  auto it = std::search (begin(haystack), end(haystack), needle1, needle1+4);

  if (it!=end(haystack))
    std::cout << "needle1 found at position " << (it-begin(haystack)) << '\n';
  else
    std::cout << "needle1 not found\n";

  return 0;
}