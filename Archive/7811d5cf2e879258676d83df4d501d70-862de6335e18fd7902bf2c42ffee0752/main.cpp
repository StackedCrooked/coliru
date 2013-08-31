#include <iostream>
#include <boost/variant.hpp>
#include <map>
using namespace std;

typedef boost::variant<int, std::string> Variant;
template<typename T>
int getIndex() { return -1; }
template<>
int getIndex<int>() { return 0; }
template<>
int getIndex<std::string>() { return 1; }


class wrapper {
    std::map<std::string, Variant> data;
public:
    template<typename T>
    boost::optional<T> get(std::string const& name) {
        auto const& val = data[name].second;
        
        if (val.which() != getIndex<T>()) 
            return boost::none;
        return boost::get<T>(v);
    }
}

int main () {
    
}