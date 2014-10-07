
#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    int v1{ 123 };
    auto v2{ 123 };
    auto v3 = { 123 };
    auto v4{ 1, 2, 3 };
    auto v5 = { 1, 2, 3 };
    
    cout << "v1's type is " << typeid(v1).name() << std::endl;
    cout << "v2's type is " << typeid(v2).name() << std::endl;
    cout << "v3's type is " << typeid(v3).name() << std::endl;
    cout << "v4's type is " << typeid(v4).name() << std::endl;
    cout << "v5's type is " << typeid(v5).name() << std::endl;

    return 0;
}
