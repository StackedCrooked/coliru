#include <iostream>
#include <string>
#include <vector>

// no warning. GCC inline it as we said.
inline __attribute__((__always_inline__)) void test(){
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
}



// not inline. Warning here
inline void test2(){
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
    std::cout <<"a";
}


int main()
{ 
   
    test();
    test2();
    
}
