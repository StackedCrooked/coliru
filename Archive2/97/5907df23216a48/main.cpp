#include <iostream>

namespace my_namespace
{
    struct X
    {
        void operator<<(int) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
        void search();
    };
    void operator<<(X, double) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

    void X::search() {
        *this << 2.5; // ADL is performed
        operator<<(*this, 2.5); // ADL is not performed => fails
    }
}

int main()
{
    my_namespace::X x;
    x.search();
}