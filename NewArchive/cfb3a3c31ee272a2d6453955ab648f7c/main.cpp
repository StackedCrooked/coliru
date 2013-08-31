#include <cassert>
#include <iostream>

class final { };

struct countdown {
    countdown(int i = 10) { assert(i); std::cout << i << std::endl; new countdown(i - 1); }
};

int main() {
    final countdown;
    (void)countdown;
}
