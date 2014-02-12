#include <iostream>
int x;
int m()
{
   // auto a=[&x]{};
 return 1;   
}
int main()
{
    int acc;
    //return by reference acc
    auto f=[&acc](int a){return acc=a*2;};
    f(5);
    std::cout <<" " <<acc;
    
}
