#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <chrono>
#include <cmath>
#include <exception>

using namespace std;
using namespace std::chrono;

#include <type_traits>

class A {
public:
    static int a;
};

void a() {}

int A::a = [](){static_assert(std::is_function<decltype(a)>::value,"'a' is not a function");return 777;}();

int main() {

    return 0;
}