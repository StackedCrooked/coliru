#include <iostream>
#include <utility>

struct check
{
   template <typename T>
   void foo(){ foo_<T>(0); }
    
private:
   template <typename T>
   decltype(std::declval<T>().value, void()) foo_(int)
   {
      std::cout << "The type has a value member.\n";
   }
   
   template <typename T>
   void foo_(long)
   {
      std::cout << "The type does not have a value member.\n";
   }
} var;

int main()
{
   struct apple
   {
      int value{};
   };
   
   struct grape{};

   var.foo<apple>();
   //var.foo<grape>();
}