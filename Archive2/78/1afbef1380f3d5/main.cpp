#include <map>
#include <tuple>
#include <typeindex>

template<typename T>
class Map {
    std::map<std::type_index, T> map_;
    
public:    
    template<typename... Ts, typename U>
    void insert(U&& u) {
        map_.emplace(typeid(std::tuple<Ts...>), std::forward<U>(u));
    }

    template<typename... Ts>
    T& at() {
        return map_.at(typeid(std::tuple<Ts...>));
    }
};

#include <iostream>
int main() {
    Map<std::string> m;
    m.insert<char>("char");
    m.insert<int, double, char>("hey");
    
    std::cout << "m.at<char>() == \"" << m.at<char>() << "\";\n"
                 "m.at<int, double, char>() == \"" << m.at<int, double, char>() << "\";\n";
}