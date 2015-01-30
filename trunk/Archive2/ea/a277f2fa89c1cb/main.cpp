#include <iostream>

struct Params { };

template <class T>
struct Base
{
    int data() const { return 42; }
};

struct Middle : private Base<Params> 
{
};

struct Final : public Middle
{
    using Base<Params>::data;
};


int main() {

    Final f;

    std::cout << f.data() << std::endl;

    return 0;
}
