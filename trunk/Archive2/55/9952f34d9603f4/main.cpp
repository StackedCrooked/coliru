#include <type_traits>
#include <iostream>

using namespace std;

int foo(int i) {
    return i;
}


struct A
{
    int foo(int i) { return i; } 
    
    auto bar(int x) -> std::result_of<decltype(&A::foo)(A, int)>::type
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
  	static_assert(std::is_same<decltype(foo(123)), int>::value, "");


	A a;
	static_assert(std::is_same<decltype(a.foo(123)), decltype(a.bar(123))>::value, "");
	static_assert(std::is_same<decltype(a.foo(123)), decltype(a.bar(123))>::value, "");
	

    auto func = &A::foo;
	static_assert(std::is_same<decltype(a.foo(123)), decltype(a.call(func, 123))>::value, "");
	static_assert(std::is_same<decltype(a.foo(123)), 
	                           std::result_of<decltype(&A::foo)(A, int)>::type
	                           >::value, "");
	

    std::cout << "SUCCESS"<< std::endl;
	return 0;
}