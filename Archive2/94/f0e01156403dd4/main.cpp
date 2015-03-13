#include <iostream>
#include <memory>

struct thing {};

// oh the horror!
thing* create_thing()
{
  std::cout << "Creating thing.\n";
  return new thing;
}
void cleanup_thing(thing* t)
{
  std::cout << "Cleaning up thing.\n";
  delete t;
}

class thing_containment
{
  std::unique_ptr<thing, decltype(&cleanup_thing)> thing_ptr;
  
public:
  thing_containment() : thing_ptr{create_thing(), &cleanup_thing} {}
};

int main()
{
  thing_containment warning_explosive;
}
  