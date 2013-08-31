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
    std::set<std::shared_ptr<std::string>, MyTypeCompare> data;
    auto ptr = std::make_shared<std::string>("HI");
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    auto ptr2 = std::make_shared<std::string>("HI");
    data.insert(ptr2);
    data.insert(ptr2);
    data.insert(ptr2);
    data.insert(ptr2);
    auto ptr3 = std::make_shared<std::string>("WORLD");
    data.insert(ptr3);
    
    for(auto& ref : data)
        std::cout << *ref << '\n';
}