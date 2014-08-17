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
        *this << 2.5; // find both because both steps are always performed
        operator<<(*this, 2.5);
        // and overload resolution selects the free function
    }
}

int main()
{
    my_namespace::X x;
    x.search();
}