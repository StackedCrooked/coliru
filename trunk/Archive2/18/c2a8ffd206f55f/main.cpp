#include <iostream>

template <typename T>
struct Class {
    Class () {
        std::cout << "Default constructor" << std::endl;
    }
    template <typename U>
    Class (const Class<U>& rhs) {
        std::cout << "Const copy constructor" << std::endl;
    }
    template <typename U>
    Class (Class<U>& rhs)
        : Class (const_cast<const Class<U>&> (rhs))
    {
        std::cout << "Copy constructor" << std::endl;
    }
};

int main() {
    Class<int> c1;
    Class<float>c2(c1);
}