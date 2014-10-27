#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
  public:
    session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { do_read(); }

  private:
    void do_read() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                boost::this_thread::sleep(boost::posix_time::milliseconds(1000)); // sleep some time
                do_write(length);
            }
        });
    }

    void do_write(std::size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                do_read();
            }
        });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class server {
  public:
    server(boost::asio::io_service &io_service, short port)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(io_service) {
        do_accept();
    }

  private:
    void do_accept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<session>(std::move(socket_))->start();
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        server s(io_service, std::atoi(argv[1]));

        boost::thread_group tg;
        for (int i=0; i < 10; ++i)
            tg.create_thread([&]{ io_service.run(); });

        tg.join_all();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
