#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

class printer
{
public:
    printer(boost::asio::io_service& io)
        : timer_(io, boost::posix_time::seconds(1)),
          count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print, this, boost::asio::placeholders::error));
    }
    ~printer()
    {
        std::cout << "Final count is " << count_ << "\n";
    }

    void print(boost::system::error_code const ec)
    {
        if (ec)
            std::cout << "Error: " << ec.message() << "\n";
        if (count_ < 5)
        {
            std::cout << count_ << "\n";
            ++count_;

            timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this, boost::asio::placeholders::error));
        }
    }

private:
    boost::asio::deadline_timer timer_;
    int count_;
};

int main()
{
    boost::asio::io_service io;
    printer p(io);
    io.run();
}
