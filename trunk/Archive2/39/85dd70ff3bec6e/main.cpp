#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>

#include <iostream>

int main()
{
    using namespace boost::asio;

    io_service io;
    posix::stream_descriptor input(io);

    input.assign(STDIN_FILENO);
    streambuf input_buffer;

    std::function<void()> loop = [&] {
        async_read_until(input, input_buffer, '\n', [&](boost::system::error_code ec, size_t) {
            if (ec) 
                std::cerr << ec.message();
            else {
                std::cout << "LOOP: '" << &input_buffer << "'\n";
                loop();
            }
        });
    };

    loop();
    io.run();
}
