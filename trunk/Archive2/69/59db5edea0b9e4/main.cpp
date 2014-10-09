#include <iostream>
#include <thread>
#include <utility>


struct Bob
{

  Bob(std::initializer_list<int>){ std::cout << "int initializer list \n";}
  Bob(std::initializer_list<double>){ std::cout << "double initializer list \n";}
  
  Bob(char c){ std::cout << "char conversion constuctorr\n";}
  
  Bob& operator+(const Bob& b){ std::cout << "bob's foo\n"; return *this;}

  operator char(){ std::cout << "bob to char\n"; return 'b';}
};   

Bob& operator+(char c, Bob& b) { std::cout << " global foo \n" ; return b;}

int main()
{

   // Bob b{3,4.5}; // ambigous
   Bob b1{3.0,4.5};
   Bob b2{3,5};
   
   b1 = 'c' +  b1;
   //b1 = b1 + 'c'; // ambiguous between built in and Bob's one... global not considered
}
