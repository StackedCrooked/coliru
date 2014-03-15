#include <boost/thread.hpp>
#include <boost/optional/optional_io.hpp>

/////////////////////////
// start condition logic

boost::mutex mx;
boost::condition_variable cv;

static bool ok_to_start = false; 

namespace /* anon detail */
{
    struct ok_to_start_predicate { bool operator()() const { return ok_to_start; } };
}

void await_start_condition()
{
    boost::unique_lock<boost::mutex> lk(mx);
    cv.wait(lk, ok_to_start_predicate());
}

void signal_start_condition()
{
    boost::lock_guard<boost::mutex> lk(mx); 
    ok_to_start = true;
    cv.notify_all();
}

/////////////////////////
// workers
static boost::optional<int> shared_secret;

void worker(int id)
{
    await_start_condition();

    // demo worker implementation
    static boost::mutex console_mx;
    boost::lock_guard<boost::mutex> lk(console_mx);
    std::cout << "worker " << id << ": secret is " << shared_secret << "\n";
}

int main()
{
    boost::thread_group threads;

    for (int i = 0; i<10; i++)
        threads.create_thread(boost::bind(worker, i));

    // demo - initialize some state before thread start
    shared_secret = 42;

    // signal threads can start
    signal_start_condition();

    // wait for all threads to finish
    threads.join_all();
}
