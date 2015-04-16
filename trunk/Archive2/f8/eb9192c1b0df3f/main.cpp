#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> map({{"key", 42}, {"some key", 24}});
    auto key = "key";
    try {
        auto value = map.at(key);
        std::cout << "I'll do something with " << value << " only if " << key << " is there\n";
    } catch (std::out_of_range const&) {
        std::cout << "otherwise I'll do something else\n";
    }
}