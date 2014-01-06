#include <iostream>
#include <vector>
#include <string>
#include <boost/serialization/variant.hpp>

namespace boost {

    std::ostream& operator<<(std::ostream& out, const std::vector<int>& v) {
        for(int i = 0; i < v.size(); ++i)
            out << " " << v[i];
        return out;
    }

}

int main() {
    boost::variant<int, std::string > a(3);
    std::cout << a << '\n'; // OK
    
    {
    using namespace boost;
    std::vector<int> b(3, 1);
    std::cout << b << '\n'; // OK
    }

    boost::variant<int, std::vector<int> > c(3);
    std::cout << c << '\n'; // ERROR
}