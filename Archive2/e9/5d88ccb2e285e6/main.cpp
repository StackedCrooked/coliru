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

const std::vector<const std::unique_ptr<Base>> CreateListOfStuff()
{
    std::vector<const std::unique_ptr<Base>> result;
    for(int i = 0; i < 3; i++)
    {
        result.push_back(CreateStuff());
    }
    return result;
}

int main()
{
  const std::vector<const std::unique_ptr<Base>> the_list = CreateListOfStuff();
  
  for(const auto& item : the_list)
  {
    item->shout(); // remember, items are pointers!
  }
}
