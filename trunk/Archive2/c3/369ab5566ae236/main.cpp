#include <iostream>
#include <limits>



struct U
{
    struct A
    {
        static int v;
        int a;
    };

    struct B
    {
       int b;
    };
};

U a;



int main()
{
    std::cout << typeid(a.A).hash_code(); 
    struct a.A b;                         
    a.A b;                          
    a.A.v = 5;                            
}

