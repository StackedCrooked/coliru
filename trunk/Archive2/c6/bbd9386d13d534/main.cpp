#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <iomanip>

using namespace boost;
using tcp = boost::asio::ip::tcp;
using byte = uint8_t;

struct crypt_t {
    crypt_t() {}
    void decrypt(byte const*, size_t offset, size_t len) {}
    int x;
};

class tcp_connection
    : public enable_shared_from_this<tcp_connection> {
public:
    typedef shared_ptr<tcp_connection> pointer;

    static pointer create(asio::io_service &ios) {
        return pointer(new tcp_connection(ios));
    }

    tcp::socket &socket() {
        return socket_;
    }

    void start() {
        byte* buf = new byte[4096];

        socket_.async_receive(asio::buffer(buf, 4096), 0,
            bind(&tcp_connection::handle_receive, shared_from_this()/*HERE!!*/,
            buf,
            std::placeholders::_1, std::placeholders::_2));
    }

private:
    tcp_connection(asio::io_service &ios)
        : socket_(ios), crypt_(new ::crypt_t())
    {
    }

    tcp_connection(tcp_connection const&) = delete;
    tcp_connection& operator=(tcp_connection const&) = delete;

    void handle_receive(byte* data, const system::error_code &err, size_t len) {
        std::cout << "Received packet of length: " << len << std::endl;

        crypt_->decrypt(data, 0, len);  // This line causes a crash, as the crypt_ pointer is invalid.

        for (size_t i = 0; i < len; ++i)
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)data[i] << ", ";

        std::cout << std::endl;
    }

    tcp::socket socket_;
    crypt_t* crypt_;
};

int main() {
    asio::io_service s;
    auto c = tcp_connection::create(s);
    c->start();
}
