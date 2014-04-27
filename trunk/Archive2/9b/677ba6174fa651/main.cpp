#include <boost/lockfree/spsc_queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <iostream>
#include <iterator>

namespace blf = boost::lockfree;

static boost::atomic_bool shutdown(false);

static void nanosleep()
{
    //boost::this_thread::yield();
    boost::this_thread::sleep_for(boost::chrono::microseconds(100));
}

struct Worker
{
    typedef blf::spsc_queue<std::string > queue;
    typedef std::unique_ptr<queue> qptr;
    qptr incoming, outgoing;
    size_t congestion = 0;

    Worker() : incoming(new queue(64)), outgoing(new queue(64)) 
    {
    }

    void operator()()
    {
        std::string request;
        while (!shutdown)
        {
            while (incoming->pop(request)) 
                while (!outgoing->push("Ack: " + request))
                    ++congestion, nanosleep();
        }
    }
};

int main()
{
    boost::thread_group g;

    std::vector<Worker> workers(10);
    std::vector<size_t> responses_received(workers.size());

    for (auto& w : workers)
        g.create_thread(boost::ref(w));

    // let's give them something to do
    const auto num_requests = (1ul<<20);
    std::string response;
    size_t congestion = 0;

    for (size_t total_sent = 0, total_received = 0; total_sent < num_requests || total_received < num_requests;)
    {
        if (total_sent < num_requests)
        {
            // send to a random worker
            auto& to = workers[rand() % workers.size()];
            if (to.incoming->push("request " + std::to_string(total_sent)))
                ++total_sent;
            else
                congestion++;
        }

        if (total_received < num_requests)
        {
            static size_t round_robin = 0;
            auto from = (++round_robin) % workers.size();
            if (workers[from].outgoing->pop(response))
            {
                ++responses_received[from];
                ++total_received;
            }
        }
    }

    auto const sum = std::accumulate(begin(responses_received), end(responses_received), size_t());
    std::cout << "\nReceived " << sum << " responses (";
    std::copy(begin(responses_received), end(responses_received), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << ")\n";

    shutdown = true;
    g.join_all();

    std::cout << "\nTotal: " << sum << " responses/" << num_requests << " requests\n";

    std::cout << "Main thread congestion: " << std::fixed << std::setprecision(1) << (100.0*congestion/num_requests) << "%\n";
    
    for (size_t idx = 0; idx < workers.size(); ++idx)
        std::cout << "Worker #" << idx << " congestion: " << std::fixed << std::setprecision(1) << (100.0*workers[idx].congestion/responses_received[idx]) << "%\n";
}
