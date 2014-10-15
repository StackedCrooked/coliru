#include <iostream>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits.hpp>

class B
{
};
     
class BDerived : public B
{
};
     
class Test
{
};
     
template<typename T>
typename boost::enable_if<boost::is_fundamental<T>, Test&>::type operator<<(Test &test, const T &v)
{
    std::cout << "T";
    return test;
}
     
Test &operator<<(Test &test, const B &v)
{
    std::cout << "B";
    return test;
}
     
void test()
{
    Test x;
    x << B() << BDerived() << 1 << 'a';
}

int main()
{
    test();
    return 0;
}