#include <iostream>
using namespace std;
int main()
{
    int i{ 5 };

    void* v = &i;

    int* t = reinterpret_cast<int*>(v);
    int u = reinterpret_cast<int&>(*v);

    int i2 = *t;

    std::cout << i2 << std::endl;
    std::cout << u << std::endl;
    return 0;
}
