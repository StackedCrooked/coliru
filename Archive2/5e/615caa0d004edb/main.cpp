#include <ctime>
#include <iostream>

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;
using namespace std;
std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}
std::string make_response()
{
    std::string response = "HTTP/1.1 200 OK\r\n";
    //response += "Transfer-Encoding: chunked\r\n";
    response += "Date: " + make_daytime_string();
    response += "Content-Length: 0\r\n";
    response += "Content-Type: text/plain;\r\n\r\n";
    return response;
}
void on_read(const boost::system::error_code& error, std::size_t bytes_transferred) {}

int main()
{
    try {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1313));
        std::cout << "listening on port 1313" << endl;

        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);


            boost::system::error_code ignored_error;

            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, "\r\n\r\n");

            std::cout << "\n\nPeer IP: " << socket.remote_endpoint().address().to_string() << std::endl;
            std::cout << "---------------------------------------------" << endl;

            std::cout << &request << endl;
            std::cout << "---------------------------------------------" << endl;

            cout << "writing response" << endl;
            boost::asio::write(socket, boost::asio::buffer(make_response()));
            cout << "ended writing" << endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
