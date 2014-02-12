#include <iostream>
#include <vector>

#include <boost/asio.hpp>

using namespace boost::asio;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(ip::tcp::socket socket)
        : socket(std::move(socket))
    {}

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        async_read_until(this->socket, buffer(this->data.data(), this->MAX_LENGTH), std::string("\n"),
            [this](boost::system::error_code ec, std::size_t length)
            {
                if (!ec) {
                    do_write(length);
                    std::cout << "Listened:" << std::endl;
                }

                do_read();
            });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        async_write(this->socket, buffer(this->data, length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
//              if (!ec) do_read();
            });
    }

    ip::tcp::socket socket;
    static constexpr int MAX_LENGTH = 1024;
//  unsigned char data[MAX_LENGTH];
    std::vector<unsigned char> data;

};

class TcpServer
{
public:
    TcpServer(io_service& io_service, short port)
        : acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
          socket(io_service)
    {
        do_accept();
    }

private:
    void do_accept()
    {
        this->acceptor.async_accept(this->socket,
            [this](boost::system::error_code ec)
            {
                if (!ec) {
                    std::make_shared<Session>(std::move(this->socket))->start();
                    std::cout << "New client!" << std::endl;
                }
                do_accept();
            });
    }

    ip::tcp::acceptor acceptor;
    ip::tcp::socket socket;
};


int main(int argc, char *argv[])
{
    std::cout << "Ohai" << std::endl;
    io_service io_serv;
    TcpServer s(io_serv, 4500);

    io_serv.run();
}