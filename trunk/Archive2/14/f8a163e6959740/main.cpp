#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

struct Y {};
struct X : Y { using Y::Y; };

auto main() -> int {
    X a;
    X b(a);
}