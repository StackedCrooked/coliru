#include <vector>

using fx_t  = char(int, char, std::vector<float> const &);
using fxp_t = fx_t*;

char foo(int, char, std::vector<float> const &) {return 0;}

fxp_t p = &foo;

int main() {}
