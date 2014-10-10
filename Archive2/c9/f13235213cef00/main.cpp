#include <boost/asio.hpp>    
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <cstring>
#include <iostream>

struct TCPSession : boost::enable_shared_from_this<TCPSession>
{
    void readData();

    TCPSession(boost::asio::io_service& svc) : socket_(svc) {
        using boost::asio::ip::tcp;
        socket_.connect(tcp::endpoint { {}, 6767 });
    }
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
};

void TCPSession::readData()
{
  auto self(shared_from_this());
  boost::asio::async_read_until(socket_, buffer_, "\r\n",
  [this, self](const boost::system::error_code& ec, std::size_t length)
  {
    std::cout << "received " << length << " bytes, ec: " << ec.message() << "\n";

    std::ostringstream ss;
    ss << &buffer_;
    std::cout << "Received data: " << ss.str();

    if (!ec){
      std::cout << "We never get here!";
      //[... process data ...]
      readData();
    }

    std::cout << "byebye\n";
  }
 );
}

int main()
{
    boost::asio::io_service svc;
    auto sess = boost::make_shared<TCPSession>(svc);

    sess->readData();
    svc.run();
}
