#include <functional>
#include <iostream>


template<typename C, typename = void>
struct GetResultType
{
    typedef void type;
};


template<typename C>
struct GetResultType<C, typename C::result_type>
{
    typedef typename C::result_type type;
};


struct Test
{
    typedef int result_type;
};


int main()
{
    static_assert(std::is_same<typename GetResultType<Test>::type, void>::value, "");
    
    static_assert(std::is_same<typename GetResultType<Test>::type, int>::value, "");
}
