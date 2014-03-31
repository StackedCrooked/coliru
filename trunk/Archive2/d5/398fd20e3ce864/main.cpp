#include <boost/asio.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <iostream>
#include <list>

typedef int                                                  ApplicationID;
typedef unsigned char                                        IPAddress[4];
typedef std::list<ApplicationID>                             APP_LIST;
typedef boost::unordered::unordered_map<IPAddress, APP_LIST> USER_MAP;

namespace boost
{
    template <> struct hash<IPAddress>
        {
            size_t operator()(IPAddress const& v) const { 
                return hash_range(v, v+4);
            }
        };
}

int main()
{
    USER_MAP map;
    map.insert({ {}, {} });
}
