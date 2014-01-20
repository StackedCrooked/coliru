#include <iostream>
#include <memory>
#include <vector>


class shape 
{
public:
  virtual ~shape() {}; // required to properly be able to delete base class pointers    
  virtual bool isRound() const = 0;
  virtual const char* name() const = 0;
};

class rectangle : public shape
{
public:
  bool isRound() const { return false; }
  const char* name() const { return "rectangle"; }
};

class circle : public shape
{
  bool isRound() const { return true; }
  const char* name() const { return "circle"; }
};

class square : public rectangle
{
  const char* name() const { return "square"; }
};

int main()
{
  std::vector<std::unique_ptr<shape>> shapes;
  shapes.emplace_back(new square());
  shapes.emplace_back(new circle());
  shapes.emplace_back(new rectangle());

  for(const auto& s : shapes)
  {
    if(s->isRound())
      std::cout << s->name() << " is round.\n";
    else
      std::cout << s->name() << " is not round.\n";
  }
}
