#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

enum A{a=170141183460469231731687303715884105727,b=-1};

int main() {

std::cout << sizeof(a) << std::endl; 
}