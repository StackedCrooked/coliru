#include <utility>
#include <string>
#include <iostream>

struct Foo {};

struct Bar {
  Bar(Foo const&) {}
};

int operator!(Foo const&) { 
  return 4; 
}

int main()
{
  Foo f;     
  std::cout << ((!f == 4) ? "meh" : "meow");
}
