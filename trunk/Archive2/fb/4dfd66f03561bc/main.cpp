#include <iostream>
#include <utility>

struct check
{
   template <typename T>
   void foo(){ foo_<T>(0); }
    
private:
   template <typename T, typename = typename std::enable_if<std::is_same<decltype(std::declval<T>().value), int>::value>::type>
   void foo_(int)
   {
      std::cout << "The type has an int value member.\n";
   }
   
   template <typename T>
   void foo_(...)
   {
      std::cout << "The type does not have an int value member.\n";
   }
} var;

int main()
{
   struct apple
   {
      int value{};
   };
   
   struct grape{
        double value{};   
    };

   var.foo<apple>();
   var.foo<grape>();
}