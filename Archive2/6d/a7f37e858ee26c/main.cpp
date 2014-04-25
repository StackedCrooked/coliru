#include <cstring>
#include <iostream>
#include <map>

struct strcmp_compare {
    using result_type = bool;
    using first_argument_type = char const*;
    using second_argument_type = char const*;

    bool operator()(char const* a, char const* b) const {
        return std::strcmp(a, b) < 0;
    }
};

int main() {
    std::map<char const*, int, strcmp_compare> map;
    map.emplace("abc", 1);
    map.emplace("cde", 2);
    map.emplace("def", 3);
    std::cout << map["abc"] << '\n';
    std::cout << map["cde"] << '\n';
    std::cout << map["def"] << '\n';
    return 0;
}
