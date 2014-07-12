#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
//#include <boost/mpl/integral_c.hpp>

struct A {
    int fA1() { std::cout << "fA1" << '\n'; return 0; };
    void fA2() { std::cout << "fA2" << '\n'; };
};

struct B {
    double fB1() { std::cout << "fB1" << '\n'; return .1; };
    void fB2() { std::cout << "fB2" << '\n'; };
};

void exampleUseOfPointerToMember() {
    A a;
    auto p = &A::fA1;
    (a.*p)();
}

using namespace boost::mpl;

// The original mpl integral wrapper has some problem with pointer to members. (value is not static in case of gcc 4.9).
// Therefore using our own wrapper for p2members.
template<typename T, T N> 
struct integral_c2 { 
  static const T value; 
  typedef integral_c2<T, N> type; 
  typedef T value_type; 
}; 
template<typename T, T N> 
typename integral_c2<T, N>::value_type const integral_c2<T, N>::value = N; 

// The dispatch table
typedef map<
      pair<A, integral_c2<decltype(&A::fA1), &A::fA1>>,
      pair<B, integral_c2<decltype(&B::fB1), &B::fB1>>
    > Assoc; 

// The desired template function
template <typename T>
auto goal(T t) -> decltype((t.*at<Assoc,T>::type::value)())
{
    auto p2Member = at<Assoc,T>::type::value;
    return (t.*p2Member)();
}
// With C++14 it would be very easy
/*template <typename T>
auto goal(T t)
{
    auto p2Member = at<Ass,T>::type::value;
    return (t.*p2Member)();
} */

    
// Usage
int main()
{
    int x = goal(A{});
    double y = goal(B{});
    (void)x, (void)y;
    return 0;
}
