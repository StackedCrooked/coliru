#include <boost/asio.hpp>
#include <array>
#include <string>
#define MAXSIZE 1000000
//...
void processCommand(std::string command)
{
    boost::asio::io_service io;
    boost::asio::ip::tcp::socket socket(io);
    boost::asio::ip::tcp::endpoint e(boost::asio::ip::address::from_string("127.0.0.1"), 60151);  //Info for the connection I need to make...

    socket.open(boost::asio::ip::tcp::v4());
    socket.connect(e);
    socket.write_some(boost::asio::buffer(command));
    socket.send(boost::asio::buffer(command));

    std::array<char, MAXSIZE> buf;
    socket.read_some(boost::asio::buffer(buf));
}

int main()
{
    processCommand("EHLO");
}
