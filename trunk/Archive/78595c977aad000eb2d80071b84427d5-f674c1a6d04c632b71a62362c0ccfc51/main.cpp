#include <set>
#include <iostream>

struct longer_is_better {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs.size() > rhs.size();
    }
};

int main()
{
    std::set<std::string> names;
    names.insert("eva");
    names.insert("peterwurst");
    names.insert("anton");

    std::cout << "lexicographical order" << std::endl;
    for(auto&& name : names)
        std::cout << name << std::endl;


    std::set<std::string, longer_is_better> names2;
    names2.insert("eva");
    names2.insert("peterwurst");
    names2.insert("anton");

    std::cout << "longer is better order" << std::endl;
    for(auto&& name : names2)
        std::cout << name << std::endl;

}