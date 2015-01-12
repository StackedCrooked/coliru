#include <iostream>
 
template<class T, class U>
auto multiplyAndAdd(T t, U u)
{
    auto a = t * u;
    auto b = a + u;
    return b;
}

void showType(float)
{
    std::cout << "float\n";
}

void showType(int)
{
    std::cout << "int\n";
}
 
int main()
{
    showType(multiplyAndAdd(1.0f, 1));
}