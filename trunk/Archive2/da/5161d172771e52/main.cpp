#include <iostream>

template<typename T, std::size_t N>
void add(T (&arr)[N])
{
    static_assert(N <= 60, "wrong size");
    // ...
}

int main()
{
  char a[60] = {  }; 
  char b[61] = { }; 
  
  add(a); // compiles 
  add(b); // doesnt compile
}