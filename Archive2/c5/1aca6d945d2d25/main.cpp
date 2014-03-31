#include <boost/asio.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <iostream>
#include <list>

typedef int                                                  ApplicationID;
typedef boost::array<unsigned char, 4>                       IPAddress;
typedef std::list<ApplicationID>                             APP_LIST;
typedef boost::unordered::unordered_map<IPAddress, APP_LIST> USER_MAP;

namespace boost
{
    template <size_t N>
    struct hash<boost::array<unsigned char, N> >
        {
            size_t operator()(boost::array<unsigned char, N> const& v) const { 
                return hash_range(v.begin(), v.end());
            }
        };
}

int main()
{
    USER_MAP map;
    IPAddress x;
    map.insert({ x, {} });
}
