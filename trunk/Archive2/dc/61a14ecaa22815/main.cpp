#include <iostream>
#include <string>


template<typename T>
using Invoke = typename T::type;


template<typename ...Conditions>
struct all;

template<typename Condition>
struct all<Condition>
{
    enum { value = Condition::value };
};

template<typename Head, typename ...Tail>
struct all<Head, Tail...> : all<Tail...>
{
    enum { value = Head::value && all<Tail...>::value };
};

template <typename... Condition>
using EnableIf = typename std::enable_if<all<Condition...>::value>::type;


template<
    typename T,
    class = EnableIf<std::is_integral<T>>,
    class = EnableIf<std::is_signed<T>>>
class Integer
{
};


int main()
{
    Integer<int> int_;
    (void)int_;
    
    //Integer<float> float_; // error
}
