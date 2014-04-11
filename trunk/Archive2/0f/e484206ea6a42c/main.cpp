#include <memory>
#include <iostream>
 
struct Foo { int i = 1; };
 
int main()
{try{
   std::weak_ptr<Foo> w_ptr;
 
   {
      auto ptr = std::make_shared<Foo>();
      w_ptr = ptr;
      std::cout << "w_ptr.use_count() inside scope: " << w_ptr.use_count() << '\n';
      std::cout << "*w_ptr inside scope: " << w_ptr.lock()->i << '\n';
   }
 
   std::cout << "w_ptr.use_count() out of scope: " << w_ptr.use_count() << '\n';
   std::cout << "*w_ptr outside scope: " << w_ptr.lock()->i << '\n';
}catch(...){
    std::cout << "oops\n";
}}