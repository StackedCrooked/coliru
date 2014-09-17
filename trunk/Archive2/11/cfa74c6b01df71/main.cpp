#include <iostream>

template<typename T, typename X, typename Y>
struct GenericFunc
{
    typedef Y (T::*F) ( X ) const ;
};

class Fct
{
public:
    Fct( /* something */) {}
    double F( double ) const
    {
        return 3.14;
    }
};

int main() {
    Fct thef;
    GenericFunc<Fct, double, double>::F phi = &Fct::F;
    std::cout << (thef.*phi)(1) << std::endl;
}