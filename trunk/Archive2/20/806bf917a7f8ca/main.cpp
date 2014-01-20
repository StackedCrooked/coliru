#include <iostream>

int main()
{
    int i{ 5 };
    void* v = &i;
    std::cout << reinterpret_cast<int&>(*v) << std::endl;
}
