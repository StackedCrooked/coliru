#include <iostream>

namespace a {
struct aa {};
}

template<typename T>
void func(T t) { do_func(t); }


int main()
{
    func( a::aa{} );
}

namespace a {
    void do_func( aa ) { std::cout << "do_func( aa )\n"; }
};