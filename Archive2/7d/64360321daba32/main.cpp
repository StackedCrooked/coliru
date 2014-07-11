#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
//#include <boost/mpl/integral_c.hpp>

struct A {
    void fA1() { std::cout << "fA1" << '\n'; };
    void fA2() { std::cout << "fA2" << '\n'; };
};

struct B {
    void fB1() { std::cout << "fB1" << '\n'; };
    void fB2() { std::cout << "fB2" << '\n'; };
};

void exampleUseOfPointerToMember() {
    A a;
    auto p = &A::fA1;
    (a.*p)();
    p = &A::fA2;
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
    > Ass; 

// The desired template function
template <typename T>
void goal(T t)
{
    auto p2Member = at<Ass,T>::type::value;
    (t.*p2Member)();
}
    
// Usage
int main()
{
    goal(A{});
    goal(B{});
    return 0;
}
