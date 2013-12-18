#include <vector>
#include <iostream>

auto counter(){
    int licznik = 0;
    return std::make_pair([=]()mutable{return ++licznik;}, [=]()mutable{return ++licznik;});
}


int test(int x){
 return ++x;
}
 
int main()
{
  {
    auto cnt = counter();
    auto inc = cnt.first;
    auto inc2 = cnt.second;
    inc();
    int x = inc();
    
    std::cout << x <<" "<< inc2();
  }
  
}