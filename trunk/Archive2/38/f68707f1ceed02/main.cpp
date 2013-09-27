#include <iostream>
#include <string>
#include <utility>

struct is_f{
    std::string name;
    
    template<class T>
    std::pair<std::string, T> operator()(T v) const{
        return {name, v};
    }
};

is_f operator""_is(char const* s, std::size_t n){
    return {{s, n}};
}

int main(){
    auto x = "hi"_is(42);
    std::cout << '"' << x.first << "\"_is(" << x.second << ")";
}