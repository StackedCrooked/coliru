#include <iostream>
#include <map>

std::map<char, bool>::iterator Add(std::map<char, bool>& mymap, char item) {
    std::pair<std::map<char, bool>::iterator, bool> result = mymap.insert(std::make_pair(item, false));
    if(!result.second) {   // Item already exists, modify that existing item
        result.first->second = false;
    }

    return result.first;
}

int main() {
    std::map<char, bool> map = { { 'a', true } };
    Add(map, 'a');
    std::cout << std::boolalpha << map['a'] << std::endl;
    auto iter = Add(map, 'b');
    std::cout << map.count('b') << ", [" << iter->first << ", " << iter->second << "]" << std::endl;
}
