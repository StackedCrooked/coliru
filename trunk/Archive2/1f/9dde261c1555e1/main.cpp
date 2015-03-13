#include <iostream>

template <template <typename ...> class P, typename ... Args>
void f(const P<Args...> &p)
{
    std::cout << "Template with " << sizeof...(Args) << " parameters!\n";
}

template <template <typename, typename> class P,typename A, typename B>
void f(const P<A, B> &p)
{
    std::cout << "Special case!\n";
}

int main(){
   f(std::pair<int,int>());   
}