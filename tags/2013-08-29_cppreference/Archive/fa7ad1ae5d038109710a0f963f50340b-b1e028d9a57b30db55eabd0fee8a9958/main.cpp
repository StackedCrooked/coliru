#include <cstddef>
#include <iostream>
#include <type_traits>

struct klass {
    std::size_t instance_size;
};

struct object {
    klass* vptr;
};

struct string {
    object base;
    char* value;
};

struct integer : object {
    int value;
};

int main() {
    std::cout << std::is_standard_layout<string>() << '\n';
    std::cout << std::is_standard_layout<integer>() << '\n';
}
