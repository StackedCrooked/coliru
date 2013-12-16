#include <iostream>
#include <stdexcept>
#include <string>
#include <utility> 

std::string format(std::string s) {
    auto pos = s.find("{}");
    if (pos != std::string::npos) {throw std::logic_error{"Not enough args"};}
    return s;   
}

template<typename Head, typename... Tail>
std::string format(std::string s, Head &&head, Tail&&... tail) {
    auto pos = s.find("{}");
    if (pos == std::string::npos) {throw std::logic_error{"Too many args"};}
    
    s.replace(pos, 2, std::to_string(head));
    return format(s, std::forward<Tail>(tail)...);
}

int main() {
    std::cout << format("Hi {} bye {}", 1, 2);
}
