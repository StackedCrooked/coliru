#include <iostream>
int main()
{
    int i = 42;
    double j = static_cast<double&&>(reinterpret_cast<double&>(i));
    std::cout << j << "\n";
}