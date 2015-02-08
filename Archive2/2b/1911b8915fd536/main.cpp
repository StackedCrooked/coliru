#include <iostream>
#include <string>
#include <functional>

template <typename E, typename Comp>
bool hasValue(E value, Comp fn) {
    return fn(value, value);
}

template <typename E>
bool hasValue(E value) {
    return hasValue(value, std::equal_to<E>());
}

struct record {
    std::string name;
    int age;
};

bool operator==(const record& r1, const record& r2) {
    bool result = false;
    if (r1.name == r2.name && r1.age == r2.age) {
        result = true;
    }
    return result;
}

int main() {
    hasValue(record{"duder", 20});
}