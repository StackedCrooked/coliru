#include <iostream>

int main()
{
    const int a = 5;
    const_cast<int&>(a)=7; //throw over const attribute in a,and assign to 7
    std::cout<<a<<std::endl; //why still out put 5!!!!!!!!!!
    
    return 0 ;
}