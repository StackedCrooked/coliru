#include <cmath>

int main() {
    static_assert(std::pow(2, 2) < 5, "foobar");
    return 0;
}
