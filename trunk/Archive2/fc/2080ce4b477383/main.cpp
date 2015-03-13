#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>

namespace ai = boost::asio;

struct foo {
    
    ai::io_service svc;
    ai::deadline_timer t{svc};

    void callback(const boost::system::error_code& error) {
        std::cout << "callback: " << error.message() << std::endl;
    }

    void set_timer(boost::posix_time::ptime time, boost::function<void(const boost::system::error_code&)> handler) {
        t.expires_at(time);
        t.async_wait(handler);
    }

    void fornow() {
        set_timer(
                boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(1),
                boost::bind (&foo::callback, this, ai::placeholders::error)
            );

        svc.run();
    }
};

int main() {
    foo o;
    o.fornow();
}
