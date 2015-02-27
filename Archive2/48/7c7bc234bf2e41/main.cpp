#include <iostream>
#include <memory>

class Foo {
};

class Bar : public Foo {
};


int main()
{
  std::shared_ptr<Bar> bar(new Bar);


  if (std::shared_ptr<Foo> foo{std::dynamic_pointer_cast<Foo>(bar)}) {
    std::cout << 1 << std::endl;
  }  

  if ( (std::shared_ptr<Foo> foo{std::dynamic_pointer_cast<Foo>(bar)}) ) {
      std::cout << 2 << std::end;
  }

  return (0);
}