#include <iostream>
#include <vector>

struct A {
    A& operator=(const A&) { return *this; }
    A& operator=(A&&) { return *this; }
    A& operator=(std::initializer_list<int>) { return *this; }
};

int main() {
    A a;
    a = { };
}