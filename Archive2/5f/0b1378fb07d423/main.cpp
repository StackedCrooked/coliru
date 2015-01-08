#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/bind.hpp>

#include <iostream>      // for debug output
#include <iomanip>

#include <linux/input.h> // for input_event
#include <boost/range/adaptor/sliced.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;

struct input {
    using error_code = boost::system::error_code;
    using sliced = boost::adaptors::sliced;

    input(const char* devspec) : svc(), sd(svc, open(devspec, O_RDONLY)) {
        readloop(); // post work
    }

    void run() {
        svc.run();
    }

  private:
    io_service svc;
    posix::stream_descriptor sd;

    std::vector<input_event> events;

    void handle_input(error_code ec, size_t bytes_transferred) {
        if (!ec) {
            auto const n = bytes_transferred / sizeof(input_event);

            for (auto& ev : events | sliced(0,n)) {
                using namespace boost::posix_time;

                ptime ts({1970,1,1}, seconds(ev.time.tv_sec) + microsec(ev.time.tv_usec));

                std::cout << std::dec << ts.time_of_day() << "\t" << std::hex 
                          << std::hex << ev.type << " " << ev.code  << " " << ev.value << "\n";
            }

            std::cout << "\n";

            readloop();
        } else {
            std::cerr << ec.message() << "\n";
        }
    }

    void readloop() {
        events.resize(32);
        sd.async_read_some(buffer(events), boost::bind(&input::handle_input, this, placeholders::error, placeholders::bytes_transferred));
    }

};

int main()
{
    input monitor("/dev/input/event2");
    monitor.run();
}
