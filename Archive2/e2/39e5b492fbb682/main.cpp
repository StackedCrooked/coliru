#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
include <chrono>
#include <cmath>
#include <exception>

using namespace std;
using namespace std::chrono;

class Foo {
public:
    ~Foo() { throw 1; }
};

int main() {
    try {
        {
            Foo();
        }
    } catch (...) {
        
    }
}