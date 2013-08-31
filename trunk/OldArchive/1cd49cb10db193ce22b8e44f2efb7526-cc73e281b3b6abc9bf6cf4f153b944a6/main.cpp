#include <vector>
#include <iostream>

namespace A {
    struct B {};
    void swap(B&,B&){}
    
    struct C {
        friend void swap(C&,C&){}
    };
}
 
template<class T>
using swap_func_type = void (*)(T &, T &);
template<class T>
swap_func_type<T> get_swap()
{
    using std::swap;
    return static_cast<swap_func_type<T>>(swap);      // Like this
}
 
int main()
{ 
    void* swapB = (void*)swap_func_type<A::B>(A::swap);
    void* foundB = (void*)get_swap<A::B>();
    std::cout << swapB << ' ' << foundB << '\n'; //works, finds A::swap
    
    void* swapC = (void*)0; //swap_func_type<A::C>(A::swap); //not sure why this fails
    void* foundC = (void*)get_swap<A::C>();
    std::cout << swapC << ' ' << foundC << '\n'; //works, finds A::C::swap
    
    void* swapV = (void*)swap_func_type<std::vector<int>>(std::swap<std::vector<int>>);
    void* foundV = (void*)get_swap<std::vector<int>>();
    std::cout << swapV << ' ' << foundV << '\n'; //cannot find std::swap<std::vector>  
}