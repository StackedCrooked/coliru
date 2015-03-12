#include <iostream>
#include <memory>
#include <vector>

class Base
{
public:
  virtual void shout() = 0;
};
class Child : public Base
{
public:
  void shout() { std::cout << "Child!\n"; }
};
class Orphan : public Base
{
public:
  void shout() { std::cout << "Orphan!\n"; }
};

int main()
{
  std::vector<std::unique_ptr<Base>> the_list;
  the_list.reserve(3);
  the_list.emplace_back(std::make_unique<Child>());
  the_list.emplace_back(std::make_unique<Orphan>());
  the_list.emplace_back(std::make_unique<Child>());
  
  for(const auto& item : the_list)
  {
    item->shout(); // remember, items are pointers!
  }
}
