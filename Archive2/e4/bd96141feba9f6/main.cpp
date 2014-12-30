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

    int n = static_cast<int>(socket_.send_to(request.data(),peer));

}

void Server::receive() {
    Peer peer;
    auto n = socket_.receive_from(boost::asio::buffer(recv_buffer_), peer);
    std::cout.write(&recv_buffer_[0], n);
    std::cout << std::endl;
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
    int n = static_cast<int>(socket_.send_to(request.data(),peer));        
}

int main(int argc, char* argv[]) {

    boost::asio::io_service io_service_client;
    boost::asio::io_service io_service_server;
    Peer peer;
    peer.address(); //Add an address here
    peer.port(12345);
    Server server(io_service_server, peer);
    Client client(io_service_client, peer);
    server.receive();
    return 0;
}