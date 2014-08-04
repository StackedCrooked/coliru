#include <iostream>

struct non_movable {
    non_movable(non_movable&&) = delete;
    explicit non_movable() = default;
};

struct aggregate {
    non_movable nv;
};

int main()
{
    []() -> aggregate { return {}; }();
    // not possible:
    // aggregate a = {};
    // return a; // <- disallowed move
}