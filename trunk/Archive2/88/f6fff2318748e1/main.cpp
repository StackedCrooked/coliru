#include <iostream>
#include <string>
#include <vector>

template<typename... Ts> void func(Ts... args){
    const int size = sizeof...(args) + 2;
    int res[size] = {1,args...,2};
    // since initializer lists guarantee sequencing, this can be used to
    // call a function on each element of a pack, in order:
    int dummy[sizeof...(Ts)] = { (std::cout << args << "T", 0)... };
}

int main()
{
  
  func(1,5,8);
}
