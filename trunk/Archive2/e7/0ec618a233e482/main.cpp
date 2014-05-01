#include <type_traits>
#include <iostream>
using namespace std;

struct A
{
    int f(int i) { return i; } 
    
    auto g(int x) -> std::result_of<decltype(&A::f)(A, int)>::type
    {  // see: http://naipc.uchicago.edu/2014/ref/cppreference/en/cpp/types/result_of.html
        return x;
    }
    
    template<typename Func, typename... Args>
    auto call(Func func, Args&&... args) const
     ->  typename std::result_of< decltype(func)(A*, Args...)>::type
 {   this->*func(args...);

 }
};


 
 
int main() {
	A a;
	static_assert(std::is_same<decltype(a.f(123)), decltype(a.g(123))>::value, "should be identical");

    auto func = &A::f;
	static_assert(std::is_same<decltype(a.f(123)), decltype(a.call(func, 123))>::value, "should be identical");
    
    
    cout << "SUCCESS";
	return 0;
}