#include <iostream>
#include <typeinfo>

template<typename T> void foo(T & arg) 
{
    // do some action on argument
    std::cout << typeid(arg).name() << std::endl;

}


int main(int, char**) {

    int array[100] = {0};
    std::cout << typeid(array).name() << std::endl;
    foo(array);

    return 0;
}