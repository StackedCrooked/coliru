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
    int i;
public:
  Child(int i) : i(i) {}
  void shout() override { std::cout << "Child " << i << "!\n"; }
};
class Orphan : public Base
{
    int i;
public:
  Orphan(int i) : i(i) {}
  void shout() override { std::cout << "Orphan " << i << "!\n"; }
};

template< typename T, typename U=T, typename ...ArgT>
std::unique_ptr<T> make_unique( ArgT ...args )
{
    return std::unique_ptr<T>( new U(args...) );
}

int main()
{
  std::vector<std::unique_ptr<Base>> the_list;
  the_list.reserve(3);
  the_list.push_back( make_unique<Base,Child> (1) );
  the_list.push_back( make_unique<Base,Orphan>(2) );
  the_list.push_back( make_unique<Base,Child> (3) );

  for(const auto& item : the_list)
  {
    item->shout(); 
  }
}
