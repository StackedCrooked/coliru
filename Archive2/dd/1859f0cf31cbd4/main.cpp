#include <iostream>
#include <thread>
#include <utility>


struct Bob
{

  Bob(std::initializer_list<int>){ std::cout << "int initializer list \n";}
  Bob(std::initializer_list<double>){ std::cout << "double initializer list \n";}
};   
int main()
{

   // Bob b{3,4.5}; // ambigous
   Bob b1{3.0,4.5};
   Bob b2{3,5};
}
