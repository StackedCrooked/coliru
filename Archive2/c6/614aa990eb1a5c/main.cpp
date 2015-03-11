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

const std::unique_ptr<Base> CreateStuff()
{
    return std::make_unique<Child>();
}

const std::vector<std::unique_ptr<Base>> CreateListOfStuff()
{
    std::vector<std::unique_ptr<Base>> result;
    for(int i = 0; i < 3; i++)
    {
        result.push_back(CreateStuff());
    }
    return result;
}

int main()
{
  std::vector<std::unique_ptr<Base>> the_list;
  the_list.reserve(3);
  the_list.emplace_back(new Child);
  the_list.emplace_back(new Orphan);
  the_list.emplace_back(new Child);
  
  for(const auto& item : the_list)
  {
    item->shout(); // remember, items are pointers!
  }
}
