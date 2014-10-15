#include <typeindex>
#include <vector>
#include <boost/functional/hash.hpp>

int main() {
    boost::hash<std::vector<std::type_index>> h;
    std::vector<std::type_index> test = { typeid(h) };
    h(test);
}