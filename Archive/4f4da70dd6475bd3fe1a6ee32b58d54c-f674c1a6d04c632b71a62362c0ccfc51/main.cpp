#include <boost/algorithm/string.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace detail {
    template<typename T>
    class map_tie_t {
    public:
        map_tie_t(std::vector<T*> variables_, std::vector<std::string> names_)
            : variables(std::move(variables_))
            , names(std::move(names_)) {

        }
        
        map_tie_t& operator=(std::unordered_map<std::string, T> const& map) {
            for (std::size_t i = 0; i < names.size(); ++i) {
                *variables[i] = map.at(names[i]);
            }
            return *this;
        }
    
    private:
        std::vector<T*> variables;
        std::vector<std::string> names;
    };
    
    template<typename T>
    T* to_pointer(T& variable) {
        return std::addressof(variable);
    }
    
    template<typename... Ts>
    map_tie_t<typename std::common_type<Ts...>::type> map_tie(std::string const& csnames, Ts&... variables) {
        std::vector<std::string> names;
        boost::split(names, csnames, boost::is_any_of(","));
        for (auto& name : names) {
            boost::trim(name);
        }

        return map_tie_t<typename std::common_type<Ts...>::type>({ to_pointer(variables)... }, std::move(names));
    }
}

#define MAP_TIE(...) ::detail::map_tie(::std::string(#__VA_ARGS__), __VA_ARGS__)

int main() {
    std::unordered_map<std::string, int> map{
        {"a", 42},
        {"b", 314},
        {"c", 1337},
    };

    int a = 0, b = 0, c = 0;
    MAP_TIE(b, c) = map;
    
    std::cout << a << ", " << b << ", " << c << '\n';
    
    return 0;
}
