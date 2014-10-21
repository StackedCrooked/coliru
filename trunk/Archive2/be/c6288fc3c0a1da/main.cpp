#include <boost/range/adaptors.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string/join.hpp>
#include <functional>

int main()
{
    using boost::asio::ip::address_v4;
    std::vector<address_v4> addresses;

    using namespace boost::adaptors;

    boost::algorithm::join(
            addresses | 
            transformed(std::mem_fn(static_cast<std::string (address_v4::*)() const>(&boost::asio::ip::address_v4::to_string))), ", ");
}
