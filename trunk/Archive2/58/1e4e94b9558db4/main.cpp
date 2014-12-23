#include <iostream>
#include <climits>

enum E { x = LONG_LONG_MAX, y };

int main(){ std::cout << y <<std::endl; }