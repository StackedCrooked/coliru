#include <boost/asio.hpp>

using boost::asio::ip::address;

address from_string_ip6(std::string const& ip)
{
    address a = address::from_string(ip);
    if (a.is_v4())
        return boost::asio::ip::address_v6::v4_mapped(a.to_v4());
    else
        return a;
}

int main()
{
    address a = from_string_ip6("192.0.2.111");
    address b = from_string_ip6("::ffff:192.0.2.111");
    address c = from_string_ip6("::ffff:c000:026f");

    assert(a == b);
    assert(a == c);
    assert(b == c);
}
