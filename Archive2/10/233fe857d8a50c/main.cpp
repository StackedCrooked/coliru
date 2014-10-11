#include <iostream>
#include <type_traits>

struct Parent {using bar = int;};
struct ChildA : public Parent {};
struct ChildB : public Parent {};

int main() {
    std::common_type<ChildA, ChildB>::bar foo = 100;
}