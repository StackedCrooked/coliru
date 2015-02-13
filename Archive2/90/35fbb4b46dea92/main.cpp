#include <boost/asio.hpp>
#include <iostream>

int main()
{
    using namespace boost::asio;

    io_service service;
    ip::tcp::endpoint endp(ip::tcp::v4(), 2001);
    ip::tcp::acceptor acc(service, endp);

    for (;;)
    {
        ip::tcp::socket sock(service);
        acc.accept(sock);
        boost::system::error_code ec;

        while (!ec)
        {
            uint8_t data[512];

            size_t len = sock.read_some(buffer(data), ec);

            if (len > 0)
            {
                std::cout << "received " << len << " bytes\n";
                write(sock, buffer("ok", 2));
            }
        }

        std::cout << "Closed: " << ec.message() << "\n";
    }
}
