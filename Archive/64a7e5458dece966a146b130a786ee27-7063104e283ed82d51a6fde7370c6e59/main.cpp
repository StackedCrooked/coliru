#include <iostream>

template<typename T, size_t N>
void array_view(const T(&array)[N]) {
    std::cout << "Viewing array";
}

int main() {
    int a[5] = {1,2,3,5};
    array_view(a);
}