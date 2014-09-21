#include <iostream>

template <class, class ...T>
void myVarFunc(T...)
{
    std::cout << "test" << std::endl;
}

typedef void(*f)(int a, char b);

int main()
{
    f myf = &myVarFunc<int>;
    myf(1, 'x');
}