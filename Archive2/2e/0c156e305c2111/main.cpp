#include <iostream>


int main()
{
  auto fact=[&fact](int n)->int{
    if(n==0)return 1;
    else    return n*fact(n-1);
  };

  std::cout<<fact(10)<<"\n";
}