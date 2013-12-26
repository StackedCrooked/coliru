#include <unordered_map>
#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>

class Thing {};

int main()
{
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<Thing>>> things;

    things[typeid(Thing)].push_back(std::make_shared<Thing>());

    auto& ptr = things[typeid(Thing)][0];

    ptr.reset(nullptr);
}