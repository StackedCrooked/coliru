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

void test() {
    A a;
    auto p = &A::fA1;
    (a.*p)();
    p = &A::fA2;
    (a.*p)();
}

using namespace boost::mpl;

template<typename T, T N> 
struct integral_c2 { 
  static const T value; 
  typedef integral_c2<T, N> type; 
  typedef T value_type; 
}; 
template<typename T, T N> 
typename integral_c2<T, N>::value_type const integral_c2<T, N>::value = N; 

typedef map<
      pair<A, integral_c2<decltype(&A::fA1), &A::fA1>>,
      pair<B, integral_c2<decltype(&B::fB1), &B::fB1>>
    > Ass; 

template <typename T>
void goal(T t)
{
    auto p2Member = at<Ass,T>::type::value;
    (t.*p2Member)();
    //(void) p2Member;
}
    
int main()
{
    goal(A{});
    goal(B{});
    return 0;
}
