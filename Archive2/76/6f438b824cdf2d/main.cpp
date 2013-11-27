#include <cstddef>
#include <iostream>

using namespace std;

template <typename ... Ts>
size_t test(Ts ... arguments) {
    auto unused = { ((cout << '[' << arguments << "]\n"), 0)...};
    (void)unused;
    return sizeof...(arguments);
}

int main() {
    test(3, 1, 4, 2, 5, 0, 2.1, "foobar");
}
