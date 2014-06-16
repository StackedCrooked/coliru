#include <iostream>
#include <type_traits>

using namespace std;

struct B
{
    ~B() {}
};

struct D1 : B
{
    ~D1() {}
};

struct D2 : D1
{
    ~D2() {}
};

int main(void)
{
    cout << std::has_virtual_destructor<B>::value << endl;
    cout << std::has_virtual_destructor<D1>::value << endl;
    cout << std::has_virtual_destructor<D2>::value << endl;
    // return 0;
}
