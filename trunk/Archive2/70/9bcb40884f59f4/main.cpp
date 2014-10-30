#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    typedef boost::asio::ip::address_v4 A;

    A address = A::from_string("192.168.0.1");

    std::cout << "Address " << address << " has broadcast address " << A::broadcast(address, A::from_string("255.255.0.0")) << "\n";
}
