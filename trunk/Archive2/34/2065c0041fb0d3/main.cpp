#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct A{
};

struct B{
   A a;
};

void test(B &&b){
    // is rvalue referenced. Its ok
    std::cout << std::is_rvalue_reference<decltype(b)>::value;
  
    // shouldn't it be also rvalue referenced?
    auto &&in = b.a;
    std::cout << std::is_rvalue_reference<decltype(in)>::value;
}


       
int main()
{
    test(B());
    
    return 0;
}
