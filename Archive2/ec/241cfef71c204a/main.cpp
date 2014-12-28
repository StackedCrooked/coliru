#include <boost/asio.hpp>

struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, 
           std::string const& host = "localhost",
           std::string const& port = "52275") 
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


#include <iostream>

static const int PORT = 52275;

void client_thread() {
    boost::asio::io_service svc;
    Client client(svc);

    client.send("hello world\n");
    client.send("bye world\n");
}

void server_thread() {
    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));

        {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::asio::streambuf sb;
            boost::system::error_code ec;
            while (boost::asio::read(socket, sb, ec)) {
                std::cout << "received: '" << &sb << "'\n";

                if (ec) {
                    std::cout << "status: " << ec.message() << "\n";
                    break;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

#include <boost/thread.hpp>

int main() {
    boost::thread_group tg;
    tg.create_thread(server_thread);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    tg.create_thread(client_thread);

    tg.join_all();
}
