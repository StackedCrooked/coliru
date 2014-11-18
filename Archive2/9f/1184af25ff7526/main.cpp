#include <iostream>
#include <boost/lexical_cast.hpp>

namespace mandala
{
    struct vec2_t {
        float x,y;
    };    
}

namespace mandala
{
    std::istream& operator>>(std::istream& istream, vec2_t& v) {
        return istream >> std::skipws >> v.x >> v.y;
    }
}

int main()
{
    auto v = boost::lexical_cast<mandala::vec2_t>("123.1 15.2");
    std::cout << "Parsed: " << v.x << ", " << v.y << "\n";
}
