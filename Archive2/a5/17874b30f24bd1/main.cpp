#include <cassert>
#include <cmath>

#define REQUIRE { [&]
#define IN (); auto result = [&]
#define ENSURE (); [&]
#define DONE (result); return result; }

double mysqrt(double x)
REQUIRE {
    assert(x >= 0.0);
} IN {
    return std::sqrt(x);
} ENSURE (auto const&) { } DONE

#include <iostream>

int main() {
    std::cout << mysqrt(9.0) << '\n';
    std::cout << mysqrt(16.0) << '\n';
    std::cout << mysqrt(-8.0) << '\n';
    return 0;
}