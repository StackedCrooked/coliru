#include <iostream>
#include <type_traits>

struct A
{
  //A() = default; // does neither compile with, nor without this line
  //A(){};           // does compile with this line
  int someVal{ 123 };


  void foobar( int )
  {
  };
};


int main()
{
    const A a;
    std::cout << "isPOD = " << std::is_pod<A>::value << std::endl;
    std::cout << "a.someVal = " <<a.someVal << std::endl;
}