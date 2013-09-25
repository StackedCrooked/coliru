#include <iostream>

template <typename T> struct C2;

template <typename T> 
struct C1
{
  template <typename Type,
        template <typename Ti> class Container = C2>
  void m() {}
};


template <typename T> 
struct C2
{
  template <typename Type = int,
        template <typename Ti> class Container = ::C2> // <-- Here is the problem!
  void m() {}

};

int main() 
{
    std::cout << "Hello World!\n";    
}