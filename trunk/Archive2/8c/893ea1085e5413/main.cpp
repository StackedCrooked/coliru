#include <iostream>

//create a template instantiation
#define INSTANTIATE(name, type) name(type)

//call a template instantiation
#define CALL(name, type, ...) name##_##type(__VA_ARGS__)

//function template must use name_type as the name
#define add(type)\
type add##_##type(type x, type y) {\
    return x + y;\
}

//library code if specific overload set
//client code if template
INSTANTIATE(add, int)

//can manually add specialization
double add_double(double, double) {
    return 1;
}

int main() {
    std::cout << CALL(add, int, 2, 3) << "\n";
    std::cout << CALL(add, double, 3.4, 5.6);
}