#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

class client
{
    public:
        client(boost::asio::io_service& io_service,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
            : deadline_(io_service),
            socket_(io_service)
    {
        boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
                boost::bind(&client::handle_connect, this,
                    boost::asio::placeholders::error));
    }

    void handle_connect(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout << "Enter message: ";
            static char const raw[] = "GET /pi/digits/pi1000000.txt HTTP/1.1\r\nHost: www.angio.net\r\nConnection: close\r\n\r\n";

            static_assert(sizeof(raw)<=sizeof(request_), "too large");

            size_t request_length = strlen(raw);
            std::copy(raw, raw+request_length, request_);

            boost::asio::async_write(socket_,
                    boost::asio::buffer(request_, request_length),
                    boost::bind(&client::handle_write, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            std::cout << "Handshake failed: " << error.message() << "\n";
        }
    }

    void deadline_expiration(const boost::system::error_code& error)
    {
        if (error == boost::asio::error::operation_aborted)
            return;

        std::cout << "\nDEADLINE REACHED\n";
        socket_.cancel();
    }

    void handle_write(const boost::system::error_code& error,
            size_t /*bytes_transferred*/)
    {
        if (!error)
        {
            std::cout << "starting read loop\n";

            deadline_.expires_from_now(boost::posix_time::millisec(800));
            //deadline_.expires_from_now(boost::posix_time::seconds(800));
            deadline_.async_wait(boost::bind(&client::deadline_expiration, this, boost::asio::placeholders::error));

            boost::asio::async_read_until(socket_,
                    //boost::asio::buffer(reply_, sizeof(reply_)),
                    reply_, '\n',
                    boost::bind(&client::handle_read, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            std::cout << "Write failed: " << error.message() << "\n";
        }
    }

    void handle_read(const boost::system::error_code& error, size_t /*bytes_transferred*/)
    {
        if (!error)
        {
            std::cout << "Reply: " << &reply_ << "\n";
            boost::asio::async_read_until(socket_,
                    //boost::asio::buffer(reply_, sizeof(reply_)),
                    reply_, '\n',
                    boost::bind(&client::handle_read, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            std::cout << "Read failed: " << error.message() << "\n";
            deadline_.cancel(); // no need for after transfer completed
        }
    }

  private:
    boost::asio::deadline_timer deadline_;
    boost::asio::ip::tcp::socket socket_;
    char request_[1024];
    boost::asio::streambuf reply_;
};

int main()
{
    try
    {
        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query("www.angio.net", "80");
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        client c(io_service, iterator);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
