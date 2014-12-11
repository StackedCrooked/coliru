#include <iostream>
using namespace std;

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

int main()
{
    Class<int> c, b(c);
}