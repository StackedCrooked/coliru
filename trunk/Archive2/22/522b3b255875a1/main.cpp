//////////////////////// test.h
#include <iostream>

//test.h
template<template <typename...> class Container>
class Test {
public:
  typedef Container<unsigned int, unsigned int> L1;
  void print() { std::cout << "GENERAL!!!" << std::endl;  }
};

//////////////////////// .cpp
#include <map>
#include <unordered_map>
#include <vector>
//#include "test.h"

template<> class Test<std::map> {
public:
  typedef std::map<unsigned int, unsigned int> L1;
  void print() { std::cout << "STD::MAP!!!" << std::endl; }
};
template<> class Test<std::unordered_map> {
public:
  typedef std::unordered_map<unsigned int, unsigned int> L1;
  void print() { std::cout << "STD::UNORDERED_MAP!!!" << std::endl; }
};

int main()
{
  Test<std::map> test3;
  test3.print();
  Test<std::unordered_map> test4;
  test4.print();
  Test<std::vector> test5;
  test5.print();
  std::cout << "COMPILES!!!" << std::endl;
  return 0;
}