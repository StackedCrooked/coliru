#include <array>
#include <iostream>
 
 class Basic {
     
     public:
     Basic();
     ~Basic();
  
     void function() {
         };
     
     private:
     void foo() {};
     
     void foo2();
     
};
     
void Basic::foo2 ()
{
    
}

Basic::Basic()
{
}
Basic::~Basic()
{
}


     
 
 class Sample : public Basic
 {
      Sample () {};
      ~Sample() {};
 };
 
 
int main()
{
    std::array<int,4> numbers {2, 4, 6, 8};
    
    int a = numbers.front();
 
    if ( a == numbers[0] )
    std::cout << " First element is equal 2 \n" ;
    std::cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = 5;
    
    
 
    std::cout << "All numbers:";
    
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    
    std::cout << '\n';
    
    std::array<int,4> n {2,4,6,8};
    
    std::cout << "All numbers:";
    for (auto j : n) {
        std::cout << ' ' << j;
    }
    std::cout << '\n';
}