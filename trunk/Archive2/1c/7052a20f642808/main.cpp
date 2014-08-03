#include<utility>
#include <type_traits>
using namespace std;

template<typename ... Args> struct A;
template<>
struct A<>{

};
template<typename First, typename ... Args>
struct A<First, Args...>:private A<Args...>{
    typedef A<Args...> child;
    typedef A<First, Args...> self;
    typedef First type;
    static const size_t size = 1 + sizeof...(Args);
    type value;
    template<typename F, typename ... Cargs>
    A(F&& first, Cargs && ... args) :child(forward<Cargs>(args)...),value(forward<F>(first)){}

};

int main() {
    int f= 6;  
    A<int, int, int> g(f, 5, f);
    A<int, int&> i(f, f);
    //A<int&, int> i2(5, f); // compile error, as expected.
}