#include <iostream>
#include <tuple>


template<typename T>
void test(const T&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    using std::make_tuple;
    test(make_tuple(make_tuple(12345, 54321, "hello!"), make_tuple(1, 2, 3, 4, 5)));
}