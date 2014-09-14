#include <iostream>
#include <type_traits>

bool compare1(float n1, float n2){
  return n1<n2;
}

bool compare2(int n1, int n2){
  return n1<n2;
}

template <typename T>
using Alias = bool(*)(T,T);

int main()
{    
    Alias<float> a = compare1;
    std::cout << a(3.14f, 5.12f) << std::endl;
        
    Alias<int> b = compare2;
    std::cout << b(1, 2) << std::endl;
}
