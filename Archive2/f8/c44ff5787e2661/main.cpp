#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using namespace boost;
using Timer = shared_ptr<asio::deadline_timer>;

asio::io_service _io;

void handler(int a, const system::error_code& = {}, Timer timer = make_shared<Timer::element_type>(_io)) {
    std::cout << "hello world\n";
    timer->expires_from_now(posix_time::seconds(1));
    timer->async_wait(bind(handler, a, asio::placeholders::error, timer));
}

int main() {
    handler(42);
    _io.run();
}
