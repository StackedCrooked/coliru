#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost;

io_service svc;
deadline_timer timer(svc);

void work()
{
    this_thread::sleep_for(chrono::milliseconds(100));
    std::cout << "Work done, rescheduling\n";
    svc.post(work);
}

void expiration_handler(system::error_code ec)
{
    if (ec != error::operation_aborted)
        svc.stop();
}

int main()
{
    svc.post(work);

    timer.expires_from_now(posix_time::seconds(2));
    timer.async_wait(expiration_handler);

    svc.run();
}


