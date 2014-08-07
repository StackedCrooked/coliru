#include <boost/algorithm/string.hpp>
#include <boost/range/adaptors.hpp>

#include <vector>
#include <string>
#include <functional>

struct IPAddress {
    std::vector<uint8_t> binaryValue;
    std::string stringValue;
};

std::string foo(std::vector<IPAddress> const& addresses)
{
    using namespace boost::adaptors;
    return boost::algorithm::join(addresses | transformed(std::mem_fn(&IPAddress::stringValue)), ";"); // Also explodes
}

#include <iostream>

int main()
{
    std::vector<IPAddress> const addresses {
        { {}, "test1" },
        { {}, "test2" },
    };
    std::cout << foo(addresses);
}
