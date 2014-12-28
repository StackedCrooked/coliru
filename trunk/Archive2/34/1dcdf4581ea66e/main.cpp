#include <boost/asio.hpp>

struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, 
           std::string const& host = "127.0.0.1",
           std::string const& port = "6767") 
        : io_service(svc), socket(io_service) 
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
        boost::asio::connect(this->socket, endpoint);
    };

    void send(std::string const& message) {
        socket.send(boost::asio::buffer(message));
    }
};

int main() {
    boost::asio::io_service svc;
    Client client(svc);

    client.send("hello world\n");
    client.send("bye world\n");
}
