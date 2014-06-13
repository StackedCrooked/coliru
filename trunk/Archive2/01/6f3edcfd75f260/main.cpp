#include <boost/asio.hpp>

using boost::asio::ip::address;

int main()
{
    address a   = address::from_string("::ffff:192.0.2.128");
    address b = address::from_string("192.0.2.128");

    assert(a == b); 
}
