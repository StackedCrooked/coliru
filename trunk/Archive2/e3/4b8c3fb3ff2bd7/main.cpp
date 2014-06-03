#include <vector>
#include <iostream>

struct base
{
  static int id;
  base() {std::cout << "C" << std::endl; mid = id; id++;}
  //base(const base&) {std::cout << "Co" << std::endl;}
  //base(base &&) {std::cout << "Mo" << std::endl;}
  ~base() {std::cout << "D" << mid << std::endl;}
  int mid;
};

int base::id = 0;

int main()
{
  std::vector<base> v;
  v.reserve(2);
  v.emplace_back();
  std::cout << "First" << std::endl;
  v.emplace_back();
  std::cout << "Second" << std::endl;
}
