#include <iostream>
#include <typeinfo>
#include <type_traits>

auto f (std::string const& s) { std::cout << s; }

#define PEOPLE ("people")

int main () {
    f PEOPLE;
}