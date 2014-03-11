
#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>

static boost::atomic_int         running_count(10);

static void worker(boost::chrono::milliseconds effort) 
{ 
    boost::this_thread::sleep_for(effort);
    --running_count;
}

int main()
{
    boost::thread_group tg;

    for (int i = 0, count = running_count; i < count; ++i) // count protects against data race!
        tg.create_thread(boost::bind(worker, boost::chrono::milliseconds(i*50)));

    while (running_count > 0)
    {
        std::cout << "Monitoring threads: " << running_count << " running\n";
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }

    tg.join_all();
}
