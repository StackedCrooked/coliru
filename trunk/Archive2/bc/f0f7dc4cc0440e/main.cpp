#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct A{
};

struct B{
   A a2;
};

//template<class B>
void test(B &&b){
    
    // 1. Correct this way?
    auto &&in3 = std::forward<B>(b).a2;
    std::cout << std::is_rvalue_reference<decltype(in3)>::value;
    
    // 2. or this
    auto &&in4 = b.a2;
    std::cout << std::is_rvalue_reference<decltype(in4)>::value;    
    
}


       
int main()
{
    test(B());
    std::cout << std::endl << " ------" << std::endl;
    //B b(A());
    //test(std::forward<B>(b));
    //test(b);
    
    return 0;
}
