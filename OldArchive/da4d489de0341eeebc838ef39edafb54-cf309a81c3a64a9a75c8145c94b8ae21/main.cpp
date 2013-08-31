#include <iostream>

enum class E {
    a,
    b
};

int main()
{
    E c = E::b;
    switch (c) {
        case E::a:
        case E::b:
            std::cout << "pass" << std::endl;
            break;
        default:
            static_assert(false, "This explodes!");
    }    
}