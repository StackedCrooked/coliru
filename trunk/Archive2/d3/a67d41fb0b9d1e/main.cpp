#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace boost;
namespace as = boost::asio;

// basically used as a callback queue for the simple reason we don't do
// asynchronous IO (yet)
as::io_service shared_queue; 

void worker(int id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 3000));

        shared_queue.post([id] {
                std::cout << "event from thread #" << id << " handled on " << this_thread::get_id << "\n";
            });
    }
}

int main() {
    thread_group threads;

    threads.create_thread(bind(worker, 1)); // arbitrary number of sources for events
    threads.create_thread(bind(worker, 2));
    threads.create_thread(bind(worker, 3));

    {
        as::io_service::work keep_running(shared_queue);
        threads.create_thread([] { shared_queue.run(); });

        this_thread::sleep_for(chrono::seconds(10));
    } // after 10 seconds, `keep_running` is destructed, bringing down the `run()` thread when idle

    threads.join_all();
}
