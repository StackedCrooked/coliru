#include <boost/lockfree/spsc_queue.hpp>
#include <boost/container/static_vector.hpp>
#include <string>
#include <thread>
#include <vector>
#include <tbb/concurrent_queue.h>


struct FilterPacket;


struct Processor
{
    void process(FilterPacket&) {}
};


struct FilterPacket
{
    FilterPacket& operator=(const FilterPacket&)
    {
        return *this;
    }

    const std::vector<Processor*> & getProcessors() const
    {
        throw std::runtime_error("Test");
    }
};

using Segment = tbb::concurrent_bounded_queue<FilterPacket>;
using SegmentQueue = tbb::concurrent_bounded_queue<Segment*>;


void processor_thread()
{
    boost::lockfree::spsc_queue<Segment*> queue(100);

    std::thread helper([&]{
        boost::container::static_vector<Segment*, 10> segments;
        segments.resize(queue.pop(segments.data(), segments.size()));
        for (Segment* segment : segments)
        {
            if (!segment)
            {
                // nullptr is used as stop signal
                return;
            }

            FilterPacket filterPacket;
            while (segment->try_pop(filterPacket))
            {
                for (Processor* processor : filterPacket.getProcessors())
                {
                    processor->process(filterPacket);
                }
            }
        }
    });

    bool is_running = true;

    while (is_running)
    {
        SegmentQueue segmentQueue;
        Segment* segment;
        while (segmentQueue.try_pop(segment))
        {
            queue.push(segment);
        }
    }

    queue.push(nullptr);
    helper.join();
}


int main()
{
}
