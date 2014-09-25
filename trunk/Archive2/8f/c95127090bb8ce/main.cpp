#include <memory>
#include <iostream>
struct Foo {
};

int main() {
  auto foo = std::shared_ptr<Foo>(nullptr, [](Foo* f){ delete f;});
  
  if (foo)
    std::cout << "foo not null\n";
  if (foo.get())
    std::cout << "foo get not null\n";    
  
  std::weak_ptr<Foo> weak_foo = foo;
  if (!weak_foo.expired())
    std::cout << "weak_foo not expired\n";
  if(weak_foo.lock())
    std::cout << "weak_foo not null\n";  
  
  
  
  Foo foo_stack;
  auto foo2 = std::shared_ptr<Foo>(std::shared_ptr<Foo>(), &foo_stack);
   
  if (foo2)
    std::cout << "foo2 not null\n";
  if (foo2.get())
    std::cout << "foo2 get not null\n";  
  
  std::weak_ptr<Foo> weak_foo2 = foo2;
  if (!weak_foo2.expired())
    std::cout << "weak_foo2 not expired\n";
  if (weak_foo2.lock())
    std::cout << "weak_foo2 not null\n";    
    if (weak_foo2.lock().get())
    std::cout << "weak_foo2 lock get not null\n";
}