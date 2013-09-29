#include <iostream>

int main() {
    static_assert(sizeof(int) == 4 && sizeof(long) == 8, "improper setup");
    static_assert(std::is_same<decltype(2147123456123), long>::value, "BOOM"); //should pass
}