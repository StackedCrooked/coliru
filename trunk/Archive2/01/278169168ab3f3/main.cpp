#include <iostream>
#include <boost/lexical_cast.hpp>

namespace mandala
{
    struct vec2_t {
        int x,y;
    };    
}

namespace mandala
{
    std::istream& operator>>(std::istream& istream, vec2_t& v) {
        std::cout << "DEBUG: " << istream.rdbuf() << "\n";
        return istream;
    }
}

int main()
{
    auto v = boost::lexical_cast<mandala::vec2_t>("1231 152");
}
