#include <iostream>
#include <complex>
using cplx = std::complex<double>;

template <typename T>
class Foo // wrapper class for a POD
{
    T val_; // this is the wrapped value
public:
    Foo(T val = {}): val_(val) {};

    template<typename S> // conversion operator
    operator S ()
    {
        std::cout << "Calling conversion operator" << std::endl;
        return val_;
    }
    // stream operator
    friend std::ostream &operator<<(std::ostream &os, const Foo &rhs)
    {
        return os << rhs.val_;
    }
};

int main()
{
    Foo<double> a = 10.1;

    // OK, calling the conversion operator double -> int
    int i = 2 + (int)a; 

    // Calling conversion operator double -> cplx
    // this line DOES NOT compile, why?! 
    cplx z = cplx(a);
}