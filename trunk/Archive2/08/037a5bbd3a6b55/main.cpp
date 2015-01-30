#include <iostream>

struct Base
{
    int data() const { return 42; }
};

struct Middle : private Base
{
};

struct Final : public Middle
{
    using Base::data;
};


int main() {

    Final f;

    std::cout << f.data() << std::endl;

    return 0;
}
