#include <iostream>
#include <memory>
using namespace std;

struct S {
    S(int X = 0, int Y = 0):x(X), y(Y){}

    S(S&& other) : x(other.x), y(other.y), ptr(std::move(other.ptr))
    {
          std::cout << "Move";
    }

    // S(const S&) {}
    // S& operator=(const S&) { return *this; }

    int x;
    int y;
    std::unique_ptr<S> ptr;
};

int main() {
    S s;
    s.ptr = std::unique_ptr<S>(new S(1, 4));
    S p = std::move(s); // Copy the pointer's value
    return 0;
}