#include <iostream>
#include <type_traits>

struct Parent {using bar = int;};
struct ChildA : public Parent {};
struct ChildB : public Parent {};

int main() {
    ChildA a_foo;
    ChildB b_foo;

    Parent implicit_a;
    implicit_a = a_foo; // * These are implicit conversions are they not?
Parent implicit_b;
    implicit_b = b_foo; // *
    
    std::common_type<ChildA&, ChildB&>::type::bar foo = 100; // so std::common_type<ChildA, ChildB>::type should be Parent because both ChildA and ChildB can be implicitly converted to Parent.
    
}