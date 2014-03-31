#include <boost/asio.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <iostream>
#include <list>

typedef int                                                  ApplicationID;
typedef boost::asio::ip::address                             IPAddress;
typedef std::list<ApplicationID>                             APP_LIST;
typedef boost::unordered::unordered_map<IPAddress, APP_LIST> USER_MAP;

namespace boost
{
    template <>
        struct hash<IPAddress>
        {
            size_t operator()(IPAddress const& v) const { 
                if (v.is_v4())
                    return v.to_v4().to_ulong();
                if (v.is_v6())
                {
                    auto const& range = v.to_v6().to_bytes();
                    return hash_range(range.begin(), range.end());
                }
                if (v.is_unspecified())
                    return 0x4751301174351161ul;
                return hash_value(v.to_string());
            }
        };
}

int main()
{
    USER_MAP map;
    map.insert({ {}, {} });
}
