#include <memory>
#include <iostream>
 
struct Foo {};
 
int main()
{
   std::weak_ptr<Foo> w_ptr;
 
   {
      auto ptr = std::make_shared<Foo>();
      w_ptr = ptr;
      std::cout << "w_ptr.use_count() inside scope: " << w_ptr.use_count() << '\n';
   }
 
   std::cout << "w_ptr.use_count() out of scope: " << w_ptr.use_count() << '\n';
}