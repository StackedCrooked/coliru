#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>

using namespace std;

struct Pimpl {
    int a;
    int b;
    int foo() {return a + b;}
};

constexpr std::size_t getPimplSize() { return sizeof(Pimpl); }

void* p = nullptr;

struct C {
    C(int a, int b) { new (reinterpret_cast<Pimpl*>(pimplMemory_)) Pimpl{a, b}; pimpl_ = reinterpret_cast<Pimpl*>(pimplMemory_); }
    ~C() { pimpl_->~Pimpl(); }
    int foo() { return pimpl_->foo(); }
    Pimpl* pimpl_;
    char pimplMemory_[getPimplSize()];
};

int main() {
    C c{3,4};
    cout << c.foo();
}
