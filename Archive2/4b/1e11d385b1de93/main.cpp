#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T>
void test(T&&)
{
    TRACE
}


int main()
{
    test([]{});
    test(+[]{});
}