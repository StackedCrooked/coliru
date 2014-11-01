#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/function.hpp>
#include <iostream>

static int device = 0;

using namespace boost;

int main() {
    boost::asio::io_service io_svc;
    boost::asio::posix::stream_descriptor iodevice(io_svc, device);

    char buffer[1024];
    function<void(system::error_code const&, size_t)> callback;
    callback = [&](boost::system::error_code const& ec, size_t bytes_transferred) {
            if (ec)
            {
                std::cout << "Error '" << ec.message() << "' during asynchronous operation\n";
            }
            else
            {
                std::cout << "Read exactly " << bytes_transferred << " bytes\n";
                std::cout << "Data: '"; 
                std::cout.write(buffer, bytes_transferred);  
                std::cout << "'\n";

                iodevice.async_read_some(asio::buffer(buffer), callback);
            }
        };
    
    iodevice.async_read_some(asio::buffer(buffer), callback);

    io_svc.run();
}
