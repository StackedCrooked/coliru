#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::ip::tcp::iostream socket("127.0.0.1","6767"); 

    std::string as_read;
    std::getline(socket,as_read);

    std::cout << as_read;
}
