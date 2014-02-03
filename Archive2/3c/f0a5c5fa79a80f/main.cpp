#include <memory>
#include <unordered_map>
#include <iostream>

int main(void)
{
  std::unordered_map<int, std::shared_ptr<int>> map;
  auto a(std::make_pair(5, std::make_shared<int>(5)));
  std::cout << "a.second is " << a.second.get() << std::endl;
  map.insert(a); // Note we are NOT doing insert(std::move(a))
  std::cout << "a.second is now " << a.second.get() << std::endl;
  return 0;
}
