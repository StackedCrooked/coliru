#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <tuple>

template<class T>
class TypeMap {
    struct hasher {
        typedef size_t result_type;
        typedef const std::type_info* argument_type;
        result_type operator()(argument_type t) const {return t->hash_code();}
    };
    std::unordered_map<const std::type_info*, T, hasher> lookup;
public:    
    template<class...Us, class...Vs>
    void insert(Vs&&...vs, std::string value) {lookup[&typeid(std::tuple<Us...>)] = std::move(value);}
    template<class...Us> T& at() {return lookup.at(&typeid(std::tuple<Us...>));}
    template<class...Us> const T& at() const {return lookup.at(&typeid(std::tuple<Us...>));}
};

#include <iostream>
#include <string>
int main()
{
    TypeMap<std::string> map;
    map.insert<int, double, char>("Hey");
    std::string& value = map.at<int, double, char>();
    std::cout << value;
}
