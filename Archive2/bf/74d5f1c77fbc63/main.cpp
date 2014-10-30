#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template< typename type_1, typename type_2 >
struct result
{
    // I want to enable these two constructors only if type_1 != type_2
    template<typename T1 = type_1, typename T2 = type_2>
    result( type_1 f, typename std::enable_if<!std::is_same<T1, T2>::value>::type * = nullptr ) : foo{f} {}
    template<typename T1 = type_1, typename T2 = type_2>
    result( type_2 b, typename std::enable_if<!std::is_same<T1, T2>::value, int>::type * = nullptr ) : bar{b} {}

    // I want to enable this constructor only if type_1 == type_2
    template<typename T1 = type_1, typename T2 = type_2>
    result( type_1 f, type_2 b, typename std::enable_if<std::is_same<T1, T2>::value>::type * = nullptr ) : foo{f}, bar{b} {}

    type_1 foo;
    type_2 bar;
};

int main()
{
   result<int, double> r(1);
   result<int, double> r2(1.0);
   
   result<int, int> r3(1, 2);
   
   // disbaled
   //result<int, double> r4(1, 2.0);
   //result<int, int> r5(1);
}
