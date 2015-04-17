#include <type_traits>
#include <iostream>
 
// foo1 overloads are enabled via the return type
template<class T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type 
    foo1(T t) 
{
    std::cout << "foo1: float\n";
    return t;
}
 
template<class T>
std::enable_if_t<std::is_integral<T>::value, T> //Using helper type
    foo1(T t) 
{
    std::cout << "foo1: int\n";
    return t;
}
 
// foo2 overload is enabled via a parameter
template<class T>
T foo2(T t, typename std::enable_if<std::is_integral<T>::value >::type* = 0) 
{
    return t;
}
 
// foo3 overload is enabled via a template parameter
template<class T ,
         typename std::enable_if<std::is_integral<T>::value>::type* = nullptr >
T foo3(T t) // note, function signature is unmodified
{
    return t;
}
 
// the partial specialization of A is enabled via a template parameter
template<class T, class Enable = void>
class A {}; // primary template
 
template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value >::type> {
}; // specialization for floating point types
 
int main()
{
    foo1(1.2); // OK, calls the first version of foo1()
    foo1(10); // OK, calls the second version of foo1()
 
//  foo2(0.1); // compile-time error
    foo2(7); // OK
 
//  foo3(1.2); // compile-time error
    foo3(34); // OK
 
    A<int> a1; // OK, matches the primary template
    A<double> a2; // OK, matches the partial specialization
}