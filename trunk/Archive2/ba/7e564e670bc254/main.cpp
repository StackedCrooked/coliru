#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>

int main() {
    auto stackoverflow = [](){ (*this)(); };
    stackoverflow();
}