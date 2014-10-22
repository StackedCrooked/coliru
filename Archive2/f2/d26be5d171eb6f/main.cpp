#include <type_traits>
#include <iostream>

template <class T>
using my_function = void(*)(T &data);

void foo(int& i) {}
void bar(float& i) {}

int main()
{
    my_function<int> fi = &foo;
    my_function<float> ff = &bar;
    
    (void)fi;(void)ff;
}
