#include <iostream>

namespace N {
  template<typename T>
  float half_of (T val) {
    return half_of (static_cast<float> (val));
  }

  template<> // comment this out to get infinite recursion
  float half_of (float val) {
    return val / 2.f;
  }
}

int
main (int argc, char *argv[])
{
  std::cout << N::half_of (123) << " ";
}