#include <iostream>
#include <string>

template<typename CharT, typename Traits, typename Predicate, typename String = std::basic_string<CharT, Traits>>
inline void all(const String& str) {
    for(auto&& i : str) {
       std::cout << i;
    }
}


int main() {
    std::cout << all(std::string("i3aa34"));
}