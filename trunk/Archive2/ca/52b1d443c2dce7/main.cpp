#include <iostream>

struct Params { };

template <class T>
struct Base
{
    int data() const { return 42; }
};

template <template <class> class D, class P>
struct Middle : private D<P> // private
{
};

struct Final : public Middle<Base,Params>
{
    using Base<Params>::data;
};


int main() {

    Final f;

    std::cout << f.data() << std::endl;

    return 0;
}
