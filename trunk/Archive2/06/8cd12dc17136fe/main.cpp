#include<iostream>

auto foo(int i) {
    if(0) return i;
   return (i == 1) ? i : foo(i-1)+i ;  
 }

int main()
{
  std::cout<< foo(5);
}