#include <iostream>
#include <type_traits>

using namespace std;

template<typename T>
// 1. auto foo(T&& arg) -> typename enable_if<is_rvalue_reference<T>::value>::type
auto foo(T&& arg) -> typename enable_if<is_rvalue_reference<decltype(arg)>::value>::type
//auto foo(T&& arg) -> typename enable_if<!is_lvalue_reference<T>::value>::type
{
     cout << is_rvalue_reference<decltype(arg)>::value  << endl;
}


int main()
{
    foo(10);
}
