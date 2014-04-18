#include <boost/thread.hpp>
#include <boost/phoenix.hpp>
#include <boost/optional.hpp>

using namespace boost;
using namespace boost::phoenix::arg_names;

boost::atomic_size_t counter(0ul);

class thread_pool
{
  private:
      mutex mx;
      condition_variable cv;

      typedef function<void()> job_t;
      std::deque<job_t> _queue;

      thread_group pool;

      boost::atomic_bool shutdown;
      static void worker_thread(thread_pool& q)
      {
          while (auto job = q.dequeue())
              (*job)();
      }

  public:
      thread_pool() : shutdown(false) {
          for (unsigned i = 0; i < boost::thread::hardware_concurrency(); ++i)
              pool.create_thread(bind(worker_thread, ref(*this)));
      }

      void enqueue(job_t job) 
      {
          lock_guard<mutex> lk(mx);
          _queue.push_back(std::move(job));

          cv.notify_one();
      }

      optional<job_t> dequeue() 
      {
          unique_lock<mutex> lk(mx);
          namespace phx = boost::phoenix;

          cv.wait(lk, phx::ref(shutdown) || !phx::empty(phx::ref(_queue)));

          if (_queue.empty())
              return none;

          auto job = std::move(_queue.front());
          _queue.pop_front();

          return std::move(job);
      }

      ~thread_pool()
      {
          shutdown = true;
          {
              lock_guard<mutex> lk(mx);
              cv.notify_all();
          }

          pool.join_all();
      }
};

static constexpr size_t bignumber = 1 << 10;

class myClass 
{
    //unsigned char readbuffer[bignumber];
    //unsigned char writebuffer[bignumber];
    void functiondostuff() { }
    void functiondomorestuff() { }

    thread_pool pool; // uses 1 thread per core

  public:
    void wreak_havoc()
    {
        std::cout << "enqueuing jobs... " << std::flush;
        for(size_t i=0; i<bignumber; ++i)
        {
            functiondostuff();
            for(int j=0; j<2; ++j) {
                functiondomorestuff();
                pool.enqueue(bind(&myClass::myFunction, this, j, i));
            }     
        }
        std::cout << "done\n";
    }

  private:
    void myFunction(int i, int j)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
        counter += 1;
    }
};

int main()
{
    myClass instance;
    instance.wreak_havoc();

    size_t last = 0;
    while (counter < (2*bignumber))
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        if ((counter >> 4u) > last)
        {
            std::cout << "Progress: " << counter << "/" << (bignumber*2) << "\n";
            last = counter >> 4u;
        }
    }
}