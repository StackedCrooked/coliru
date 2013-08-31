#include <tuple>
#include <iostream>
#include <iomanip>

using std::tuple;

int main() {
    std::cout << std::boolalpha << std::is_same<tuple<>, tuple<void>>::value;
}

