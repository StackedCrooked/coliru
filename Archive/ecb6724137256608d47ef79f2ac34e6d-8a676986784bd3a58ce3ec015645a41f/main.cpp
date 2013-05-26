#include <utility>

struct check
{
   template <typename T>
   decltype(std::declval<T>().value, void()) foo()
   {
      static_assert(T{}.value == 10, "Incorrect value");
   }
   
   template <typename T>
   auto foo() -> decltype(std::declval<T>().value2, void())
   {
      static_assert(T{}.value2 == 0, "Incorrect value");
   }
} var;

int main()
{
   struct apple
   {
      int value2{};
   };

   var.foo<apple>();
}