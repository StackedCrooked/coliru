#include <cstddef> // for NULL
#include <iostream>

class null_value_type;

struct container_traits {
    static null_value_type get_array_pointer();
};

class null_value_type {
 public:
    operator int*() {
        return NULL;
    }
    
    friend null_value_type container_traits::get_array_pointer();
 private:
    null_value_type() {}
};

null_value_type container_traits::get_array_pointer() {
    return null_value_type();
}

int main() {
    int *p = container_traits::get_array_pointer();
    if (p == NULL) std::cout << "Success!\n";
    return 0;
}
