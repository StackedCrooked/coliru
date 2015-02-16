#include <cassert>
#include <cmath>

#define REQUIRE { [&]
#define IN (); auto result = [&]
#define ENSURE (); [&]
#define DONE (result); return result; }

double myabs(double x)
REQUIRE { } IN {
    return x;
} ENSURE (auto const& result) {
    assert(result >= 0);
} DONE

#include <iostream>

int main() {
    std::cout << myabs(9.0) << '\n';
    std::cout << myabs(16.0) << '\n';
    std::cout << myabs(-8.0) << '\n';
    return 0;
}