#include <boost/asio.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {

    typedef boost::asio::ip::address_v4 A4;
    boost::asio::io_service s;
    tcp::resolver r(s);

    for (auto const& a : boost::make_iterator_range(r.resolve({"127.0.0.1", "80"}), {}))
        try { 
            A4 v4 = a.endpoint().address().to_v4();
            
            std::cout << v4 << " -> "
                      << A4::broadcast(v4, A4::netmask(v4))
                      << "\n"; 
        }
        catch(...) { std::cout << "No ipv4 broadcast for " << a.endpoint() << "\n"; }
}
