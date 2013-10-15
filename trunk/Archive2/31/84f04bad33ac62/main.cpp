#include <iostream>

#define INSTANTIATE(name, type) name(type)
#define CALL(name, type, ...) name##_##type(__VA_ARGS__)

#define add(type)\
type add##_##type(type x, type y) {\
    return x + y;\
}

INSTANTIATE(add, int)

double add_double(double x, double y) {
    return 1;
}

int main() {
    std::cout << CALL(add, int, 2, 3) << "\n";
    std::cout << CALL(add, double, 3.4, 5.6);
}