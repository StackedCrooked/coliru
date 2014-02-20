#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>

boost::asio::io_service my_io_service;
boost::asio::posix::stream_descriptor in(my_io_service, ::dup(STDIN_FILENO));

// perform reading loop
void reading_loop()
{
    std::cerr << "(continueing input...)\n";
    static boost::asio::streambuf buffer; // todo some encapsulation :)

    async_read_until(in, buffer, '\n', [&](boost::system::error_code ec, size_t bytes_transferred) {
            if (!ec)
            {
                std::string line;
                std::istream is(&buffer);
                if (std::getline(is, line) && line == "exit")
                    ec = boost::asio::error::operation_aborted;
                else
                    reading_loop(); // continue
            } 

            if (ec)
            {
                std::cerr << "Exiting due to: " << ec.message() << "\n";
            }
    });
}

int main() {
    reading_loop();
    my_io_service.run();
}
