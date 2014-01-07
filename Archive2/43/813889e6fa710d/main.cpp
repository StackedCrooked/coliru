#include <iostream>
int main()
{
    int const x = 1;
    std::cout << "before modification: " << x << "\n";
    *const_cast<int*>(&x) = 42;
    std::cout << "after modification: " << x << "\n";
}