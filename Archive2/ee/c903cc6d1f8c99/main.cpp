#include <iostream>
#include <limits>


struct Y {
    Y(){ std::cout << "Y()" << std::endl; };
    Y(const Y&){ std::cout << "Y(const Y&)" << std::endl; };
    Y(Y&&){ std::cout << "Y(const Y&&)" << std::endl; };
};

Y f(int)
{
    return Y();
}

Y d(f(1)); // calls Y(Y&&)
Y e = d; // calls Y(const Y&)

int main(){ }

