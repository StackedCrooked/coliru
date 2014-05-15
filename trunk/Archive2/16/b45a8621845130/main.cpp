#include <iostream>
#include <cmath>
#include <map>
#include <unordered_map>
using namespace std; 

class TestEntry {};
//.h
template<template <typename...> class Container>
class Test {
  typedef Container<unsigned int, TestEntry> L1;
};

//.cpp
template<> class Test<std::map> { public:     typedef std::map<unsigned int, unsigned int> L1;  };
template<> class Test<std::unordered_map> { public:     typedef std::unordered_map<unsigned int, unsigned int> L1; };

template<template <typename...> class Container>
class Test2 {
  Test<Container> L1;
};

template<> class Test2<std::map> {     public: 		Test<std::map> test; 	};

int main()
{
  
  std::cout << "COMPILES!!!" << std::endl;
  return 0;
}
