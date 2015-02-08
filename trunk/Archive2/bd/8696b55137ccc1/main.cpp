#include <iostream>
#include <string>
#include <functional>

template <typename E, typename Comp>
bool hasValue(E value, Comp fn = std::equal_to<E>()){
    return fn(value, value);
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