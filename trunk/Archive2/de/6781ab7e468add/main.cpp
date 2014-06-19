#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::io_service ios;

    std::cout << "using Boost " << BOOST_LIB_VERSION << std::endl;
    
    ios.post([](){});   // add something
    ios.stop();         // Subsequent calls to run(), run_one(), poll() or poll_one() will return immediately until reset() is called.

    boost::system::error_code ec;
    size_t re = ios.poll_one(ec);
    std::cout << "poll after stop: handled " << re << ", stopped " << std::boolalpha << ios.stopped() << ", error " << ec << std::endl;
    return 0;
}
