#include <iostream>
#include <memory>
#include <set>

struct MyTypeCompare
{
  bool operator()(const std::shared_ptr<std::string>, const std::shared_ptr<std::string>) const;
};

bool MyTypeCompare::operator()(const std::shared_ptr<std::string> p1,
                                 const std::shared_ptr<std::string> p2) const
{
  return *p1 < *p2;
}

int main() {
    std::set<std::shared_ptr<std::string>, MyTypeCompare> set;
    auto ptr = std::make_shared<std::string>("HI");
    set.insert(ptr);
    set.insert(ptr);
    set.insert(ptr);
    set.insert(ptr);
    set.insert(ptr);
    set.insert(ptr);
    auto ptr2 = std::make_shared<std::string>("HI");
    set.insert(ptr2);
    std::cout << set.size();
}