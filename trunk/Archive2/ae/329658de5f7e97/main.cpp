#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

struct Base { Base(int) {} };
struct D1 : virtual Base { using Base::Base; };

struct D2 : D1 { };

int main() {
    D1 d(5);
}