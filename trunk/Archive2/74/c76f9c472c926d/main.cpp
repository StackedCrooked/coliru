#include<string>
#include<iostream>

struct Init {
  std::string s;
  int i;
};

Init a;
int main() {
  Init b{};
  Init c;

  if(a.s == b.s)
    std::cout << "a.s == b.s" <<std::endl;
  else
      std::cout << "fasszom\n";
  if(a.s == c.s)
    std::cout << "a.s == c.s" <<std::endl;
  else
      std::cout << "fasszom\n";
  if(a.i == b.i)
    std::cout << "a.i == b.i" <<std::endl;
  else
      std::cout << "fasszom\n";
  if(a.i == b.i)
    std::cout << "a.s == c.i" <<std::endl;
  else
      std::cout << "fasszom\n";
}
