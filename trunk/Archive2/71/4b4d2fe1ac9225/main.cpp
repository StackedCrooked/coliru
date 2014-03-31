#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <iostream>

struct Program
{
    boost::array<char, 1024> _buf;
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::socket _socket;
    std::stringstream _received;

    void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Transferred " << bytes_transferred << "bytes." << std::endl;
            _received.write(_buf.data(), bytes_transferred);

            _socket.async_receive(boost::asio::buffer(_buf),
                    boost::bind(&Program::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        } else
        {
            std::cout << "End of transfer reached: " << error.message() << "\n";
            std::cout << "------------------------------------------------------------\n";
            std::cout << "Data: '" << _received.str() << "'\n";
        }
    }

    void connect_handler(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout << "Connected to server successfully." << std::endl;

            _socket.async_receive(boost::asio::buffer(_buf),
                    boost::bind(&Program::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            
            // this is synchronous, but it could be done using async_* as well:
            _socket.send(boost::asio::buffer("GET / HTTP/1.0\r\nHost: www.google.com\r\n\r\n"));
        }
    }

    Program(std::string const& host, std::string const& service)
        : _buf(), _io_service(), _socket(_io_service), _host(host), _service(service) 
    {
    }

    int run()
    {
        boost::asio::ip::tcp::resolver resolver(_io_service);
        boost::asio::ip::tcp::resolver::query query(_host, _service, boost::asio::ip::resolver_query_base::numeric_service);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        boost::asio::async_connect(_socket, endpoint_iterator, boost::bind(&Program::connect_handler, this, boost::asio::placeholders::error));
        _io_service.run();

        return 0;
    }

    std::string const _host;
    std::string const _service;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }

        Program program(argv[1], argv[2]);
        return program.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


}
