#include <iostream>
using namespace std;

constexpr int do_something(int x)
{
  static_assert(x > 0, "x must be > 0");
  return x + 5;
}

int do_something(int x)
{
  if(x > 0) { cout << "x must be > 0" << endl; exit(-1); }
  return x + 5;
}

int main(int argc, char* argv[])
{
    std::cout << do_something(7) << std::endl;
    std::cout << do_somathing(argc) << std::endl;
    
    return 0;
}