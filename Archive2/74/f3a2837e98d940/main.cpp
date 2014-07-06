#include <iostream>
#include <string>
#include <vector>


inline void test(){
    std::cout <<"a";
}

inline void fire(void (*fun)()){
    fun();
}

int main()
{ 
    //void (*fun1)() = &test;
    fire(&test);
}
