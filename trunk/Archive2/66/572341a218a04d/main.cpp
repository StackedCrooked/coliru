#include<array>
#include<boost/asio.hpp>
#include<iostream>

using Peer = boost::asio::ip::udp::endpoint;
using namespace boost::asio::ip;


class Server {
public:
    Server(boost::asio::io_service& io_service, Peer peer);
    void receive();

private:
    boost::asio::ip::udp::socket socket_;
    std::array<char, 1024> recv_buffer_;
};

Server::Server(boost::asio::io_service& io_service, Peer peer) :
    socket_(io_service, Peer(boost::asio::ip::udp::v6(), peer.port())),
    recv_buffer_()
{
    boost::asio::streambuf request;
    std::ostream os(&request);
    os << "Server";

    boost::system::error_code error;
    auto bytes_transferred = socket_.send_to(request.data(), peer, 0, error);
    std::cout << "Server sent: " << bytes_transferred << " bytes"
                 " with " << error.message() << std::endl;
}

void Server::receive() {
    Peer peer;
    boost::system::error_code error;
    auto bytes_transferred =
      socket_.receive_from(boost::asio::buffer(recv_buffer_), peer, 0, error);
    std::cout << "Server received " << bytes_transferred << " bytes"
                 " from " << peer
              << " with " << error.message() << std::endl;
    if (!error) {
      std::cout << "  >> ";
      std::cout.write(recv_buffer_.data(), bytes_transferred);
      std::cout << std::endl;
    }
    receive();
}

class Client {
public:
    Client(boost::asio::io_service& io_service, Peer peer);
    void send(Peer peer);

private:
    boost::asio::ip::udp::socket socket_;
};


Client::Client(boost::asio::io_service& io_service, Peer peer) : socket_(io_service) {
    socket_.open(boost::asio::ip::udp::v6());
    send(peer);
}

void Client::send(Peer peer) {
    boost::asio::streambuf request;
    std::ostream os(&request);
    os << "Client";
    boost::system::error_code error;
    auto bytes_transferred = socket_.send_to(request.data(), peer, 0, error);
    std::cout << "Client sent: " << bytes_transferred << " bytes"
                 " with " << error.message() << std::endl;      
}

int main(int argc, char* argv[]) {

    boost::asio::io_service io_service_client;
    boost::asio::io_service io_service_server;
    Peer peer;
    peer.address(boost::asio::ip::address_v6::loopback());
    peer.port(12345);
    Server server(io_service_server, peer);
    Client client(io_service_client, peer);
    server.receive();
    return 0;
}