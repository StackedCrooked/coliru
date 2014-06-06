#include <iostream>
namespace A{
    extern int k;

    int i = 4;
}
int i=3;
int A::k  = i;

int main()
{


   std::cout << A::k;    
   A::k = i;
   std::cout << A::k;    
   
}