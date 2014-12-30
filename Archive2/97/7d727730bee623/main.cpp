#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace asio = boost::asio;
using asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> sptr;

    tcp_connection(asio::io_service& io_service) : socket_(io_service), timer_(io_service)
    {
    }

    void start()
    {
        std::cout << "Created tcp_connection session\n";

        // post some work bound to this object; if you don't, the client gets
        // 'garbage collected' as the ref count goes to zero
        do_hello();
    }

    ~tcp_connection() {
        std::cout << "Destroyed tcp_connection\n";
    }

    tcp::socket& socket()
    {
        return socket_;
    }

  private:
    tcp::socket socket_;
    asio::deadline_timer timer_;

    void do_hello(boost::system::error_code const& ec = {}) {
        if (!ec) {
            asio::async_write(socket_, asio::buffer("Hello world\n"),
                    boost::bind(&tcp_connection::handle_written, shared_from_this(), asio::placeholders::error, asio::placeholders::bytes_transferred)
                );
        }
    }

    void handle_written(boost::system::error_code const& ec, size_t /*bytes_transferred*/) {
        if (!ec) {
            timer_.expires_from_now(boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&tcp_connection::do_hello, shared_from_this(), asio::placeholders::error));
        }
    }
};

class tcp_server
{
public:
    tcp_server(asio::io_service& io_service)
        : io_service_(io_service),
          acceptor_(io_service, tcp::endpoint(tcp::v4(), 6767))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        tcp_connection::sptr new_connection = boost::make_shared<tcp_connection>(io_service_);
        acceptor_.async_accept(new_connection->socket(),
                boost::bind(
                    &tcp_server::handle_accept,
                    this, new_connection, asio::placeholders::error
                )
            );
    }

    void handle_accept(tcp_connection::sptr client, boost::system::error_code const& error)
    {
        if (!error)
        {
            client->start();
            start_accept();
        }
    }

    asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};

int main()
{
    try
    {
        asio::io_service io_service;
        tcp_server server(io_service);

        boost::thread(boost::bind(&asio::io_service::run, &io_service)).detach();

        boost::this_thread::sleep_for(boost::chrono::seconds(4));
        io_service.stop();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
