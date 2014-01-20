#include <iostream>
#include <math.h>
#include <string>

template<int>
struct TakesInt{};


struct True
{
};

struct False
{
  // guarantees that sizeof(False) != sizeof(True)
  True array[2];
};


// takes anything; fall back if no match can be found
template<typename T>
False overload(...);

// As a test, this is an overload of log that takes a string.
// I don't actually want to implement this, but it should make the compiler
// think that a string is a valid argument.
double log(std::string);

// takes a specific type; does not actually call log
template<typename T>
True overload(TakesInt<sizeof(log(T()))>*);


// a placeholder for user defined class; could really be anything,
// like an arbitrary number class
struct MyClass{};

// declaring log for the arbitrary class above
// note that this is the same as for the log(std::string)
// if one works, the other should
double log(MyClass);

int main()
{
  std::cout << sizeof(True) << '\t' << sizeof(False) << std::endl;
  std::cout << sizeof(overload<std::string>(NULL)) << std::endl;
  std::cout << sizeof(overload<double>(NULL)) << std::endl;
  std::cout << sizeof(overload<MyClass >(NULL)) << std::endl;
  return 0;
}