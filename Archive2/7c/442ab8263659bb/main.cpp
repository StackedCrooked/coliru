#include <unordered_map>
#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>

struct thing {};

struct withmap
{
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<thing>>> stuff;

public:
    withmap() {}
};


#include <iostream>
int main()
{
    std::cout << "done\n";
}