#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <iostream>

static int device = 0;

int main() {
    boost::asio::io_service io_svc;
    boost::asio::posix::stream_descriptor iodevice(io_svc, device);

    uint8_t buffer[10];
    boost::asio::async_read(iodevice, 
            boost::asio::buffer(buffer), 
            boost::asio::transfer_exactly(10),
            [&buffer](boost::system::error_code const& ec, size_t bytes_transferred) {
                if (ec)
                {
                    std::cout << "Error '" << ec.message() << "' during asynchronous operation\n";
                }
                else
                {
                    std::cout << "Read exactly " << bytes_transferred << " bytes\n";
                    std::cout << "Data: '" << std::string(buffer, buffer+sizeof(buffer)) << "'\n";
                }
            });

    io_svc.run();
}
