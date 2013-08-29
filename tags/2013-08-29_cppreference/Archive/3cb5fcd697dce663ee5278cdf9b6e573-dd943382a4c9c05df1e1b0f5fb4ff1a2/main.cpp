#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio::ip;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(tcp::socket&& socket) : socket_(std::move(socket)) {}
private:
    tcp::socket socket_;
};

int
main()
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket socket( ios );
    const std::shared_ptr<Connection> connection( new Connection(std::move(socket)) );
}