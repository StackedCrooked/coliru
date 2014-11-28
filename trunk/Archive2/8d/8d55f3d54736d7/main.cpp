#include <iostream>

template <typename T>
class C
{
public:
    C() { }
    C(int) { T t; }
};

class NoDefCtor
{
public:
    NoDefCtor(int) { }
};

int main()
{
    C<NoDefCtor> c;
    std::cout << "sucs..?" << std::endl;
}