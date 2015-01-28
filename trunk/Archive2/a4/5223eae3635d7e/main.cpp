#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

struct Foo
{
    void Bar() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

int main()
{
    std::unordered_map<std::string, std::shared_ptr<Foo>> map;
    map["key i'm looking for"] = std::make_shared<Foo>();
    auto result = map.find("key i'm looking for");
    result->second->Bar();
}
