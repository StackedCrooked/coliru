#include <iostream>

struct A
{
    template <typename T>
    static void foo(){ }
    
    template <typename T>
    static int foo(){ return 0; }
};

int main(){ }