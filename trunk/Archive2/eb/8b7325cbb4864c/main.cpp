#include <iostream>
#include <boost/lexical_cast.hpp>

struct vec2_t
{
    float x;
    float y;
};

std::istream& operator>>(std::istream& istream, vec2_t& v)
{
    istream >> v.x >> v.y;

    return istream;
}

int main()
{
    auto v = boost::lexical_cast<vec2_t>("1231.2 152.9");

    std::cout << v.x << " " << v.y;

    return 0;
}