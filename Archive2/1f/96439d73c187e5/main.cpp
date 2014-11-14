#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;
using asio::ip::tcp;

struct ServerSocket
{
    asio::io_service _io_service;
    tcp::endpoint _endpoint;
    tcp::acceptor _acceptor;
    asio::deadline_timer _timer;
    bool _newConnection;

    ServerSocket(unsigned int port)
        : _io_service(),
          _endpoint(tcp::v4(), port),
          _acceptor(_io_service, _endpoint),
          _timer(_io_service),
          _newConnection(false)
    {
    }

    void timer_expired(boost::system::error_code ec)
    {
        if (!ec)
        {
            _acceptor.cancel();
        }
    }

    bool accept(boost::asio::ip::tcp::socket& socket, int timeout)
    {
        _newConnection = false;
        _io_service.reset();
        _timer.expires_from_now(boost::posix_time::seconds(timeout));
        _timer.async_wait(boost::bind(&ServerSocket::timer_expired, this, asio::placeholders::error));
        _acceptor.async_accept(socket, boost::bind(&ServerSocket::handleAccept, this, &socket, asio::placeholders::error));

        _io_service.run();

        return _newConnection;
    }

    void handleAccept(boost::asio::ip::tcp::socket* pSocket, boost::system::error_code ec)
    {
        if (!ec)
        {
            _timer.cancel();
            _newConnection = true;
        }
    };
};

#include <iostream> 

int main()
{
    ServerSocket s(6767);

    tcp::socket socket(s._io_service);

    if (s.accept(socket, 3))
        std::cout << "Accepted connection from " << socket.remote_endpoint() << "\n";
    else
        std::cout << "Timeout expired\n";
}
