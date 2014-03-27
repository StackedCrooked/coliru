#include <iostream>

template<class Type, std::size_t N>
void reset(Type (&array)[N]) {
    for (auto& i : array)
        i = Type(0);
}

int main() {
    int x[42] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    reset(x);
}