//
// QUIZ: Can you predict which samples will be accepted
//        and which will be rejected by the compiler?


#include <iostream>


template<typename T>
void test(T&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }


int main()
{   
    // 1
    int a = 68;
    test(a); 
    
    
    // 2
    const int b = 200;
    test(b); 


    // 3
    //test(42); 
}
