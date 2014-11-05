#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::system::error_code ec;
    using namespace boost::asio;

    // what we need
    io_service svc;
    ip::tcp::socket sock(svc);
    sock.connect({ {}, 8087 }); // http://localhost:8087 for test

    // send request
    std::string request("GET /newGame?name=david HTTP/1.1\r\n\r\n");
    sock.send(buffer(request));

    // read response
    std::string response;
    
    do {
        char buf[1024];
        size_t bytes_transferred = sock.receive(buffer(buf), {}, ec);
        if (!ec) response.append(buf, buf + bytes_transferred);
    } while (!ec);

    // print and exit
    std::cout << "Response received: '" << response << "'\n";
}
