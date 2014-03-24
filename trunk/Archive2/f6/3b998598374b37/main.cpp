#include <boost/thread.hpp>
#include <boost/optional.hpp>
#include <boost/lockfree/queue.hpp>

using namespace boost;

template <typename job_t>
class thread_pool
{
    static_assert(boost::has_trivial_destructor<job_t>::value, "requirement not met");
  private:
    typedef boost::lockfree::queue<job_t, boost::lockfree::capacity<65520>> queue_t;

    queue_t _queue;
    thread_group pool;
    boost::atomic_bool shutdown;

    static void worker_thread(thread_pool& q)
    {
        job_t job;

        while (!q.shutdown)
            while (q.dequeue(job))
                job();

        while (q.dequeue(job))
            job();
    }

    public:
    thread_pool() : shutdown(false) {
        for (unsigned i = 0; i < 12*boost::thread::hardware_concurrency(); ++i)
            pool.create_thread(bind(worker_thread, ref(*this)));
    }

    void enqueue(job_t const& job) 
    {
        while (!_queue.push(job))
        {
            /* IDEA: don't flood the queue when saturated?
             *
             * Depends on the avg. running time of jobs and the load they
             * produce
             */
            // this_thread::sleep_for(chrono::microseconds(5))
        }
    }

    bool dequeue(job_t& job) 
    {
        return _queue.pop(job);
    }

    ~thread_pool()
    {
        shutdown = true;
        pool.join_all();
    }
};

boost::atomic_size_t counter(0ul);

static constexpr size_t bignumber = 1 << 20;

class myClass 
{
    //unsigned char readbuffer[bignumber];
    //unsigned char writebuffer[bignumber];
    void functiondostuff() { }
    void functiondomorestuff() { }

    struct myJob {
        size_t i;
        int j;

        void operator()() const { 
            // NO SLEEP in the jobs: this_thread::sleep_for(chrono::microseconds(10));
            counter += 1; 
        }
    };

    thread_pool<myJob> pool; // uses 1 thread per core

  public:
    void wreak_havoc()
    {
        for(size_t i=0; i<bignumber; ++i)
        {
            functiondostuff();
            for(int j=0; j<2; ++j) {
                functiondomorestuff();
                pool.enqueue(myJob { i, j });
            }     
        }
    }
};

int main()
{
    myClass instance;
    thread([&] { instance.wreak_havoc(); }).detach();

    size_t last = 0;
    do 
    {
        if ((counter >> 4u) > last)
        {
            std::cout << "Progress: " << counter << "/" << (bignumber*2) << "\n";
            last = counter >> 4u;
        }

        if (counter < (2*bignumber))
        {
            boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        }
    } while (counter < (2*bignumber));

    std::cout << "Leaving grand hotel: " << counter << "\n";
}
