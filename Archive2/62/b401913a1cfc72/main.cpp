#include <iostream>
#include <vector>

struct foo
{
    void bar()       { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    void bar() const { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

int main() 
{
  std::vector<foo> foos{foo{}, foo{}};
  
  std::cout << "---- auto const& ----\n";
  for(auto const& f : foos) {
      f.bar();
  }
  std::cout << "---- auto& ----\n";
  for(auto& f : foos) {
      f.bar();
  }
  std::cout << "---- auto&& ----\n";
  for(auto&& f : foos) {
      f.bar();
  }
}
