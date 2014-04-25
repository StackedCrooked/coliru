#include <boost/lockfree/spsc_queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <iostream>
#include <iterator>

namespace blf = boost::lockfree;

static boost::atomic_bool shutdown(false);

struct Worker
{
    typedef blf::spsc_queue<std::string > queue;
    typedef std::unique_ptr<queue> qptr;
    qptr incoming, outgoing;

    Worker() : incoming(new queue(1024)), outgoing(new queue(1024)) 
    {
    }

    void operator()()
    {
        std::string request;
        while (!shutdown)
        {
            while (incoming->pop(request)) outgoing->push("Ack: " + request);
        }
        while (incoming->pop(request)) outgoing->push("Ack: " + request);
    }
};

int main()
{
    boost::thread_group g;

    std::vector<Worker> workers(10);
    std::vector<size_t> responses_received(workers.size());

    for (auto& w : workers)
        g.create_thread(boost::ref(w));

    // let's given them something to do
    const auto num_requests = (1ul<<20);
    std::string response;
    for (size_t i = 0; i < num_requests; ++i)
    {
        // send to a random worker
        auto& w = workers[rand()%workers.size()];
        w.incoming->push("request " + std::to_string(i));

        // scheduled processing of responses
        int round_robin = i%workers.size();
        if (workers[round_robin].outgoing->pop(response))
        {
            ++responses_received[round_robin];
        }
    }

    auto const sum = std::accumulate(begin(responses_received), end(responses_received), size_t());
    std::cout << "\nReceived " << sum << " responses (";
    std::copy(begin(responses_received), end(responses_received), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << ")\n";

    shutdown = true;
    g.join_all();

    size_t late_arrivals = 0;

    for (auto& w : workers)
    {
        while (w.outgoing->pop(response))
        {
            ++late_arrivals;
        }
    }
    std::cout << "\nLate arrivals: " << late_arrivals << " (total: " << (sum + late_arrivals) << " responses/" << num_requests << " requests)\n";
}


