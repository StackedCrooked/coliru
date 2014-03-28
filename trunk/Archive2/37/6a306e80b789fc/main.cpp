#include <boost/thread.hpp>
#include <boost/phoenix.hpp>
#include <boost/optional.hpp>

using namespace boost;
using namespace boost::phoenix::arg_names;

boost::atomic_size_t counter(0ul);

class thread_pool
{
  private:
      mutable mutex mx;
      mutable condition_variable cv;

      typedef function<void()> job_t;
      std::deque<job_t> _queue;

      thread_group pool;

      boost::atomic_bool shutdown;
      static void worker_thread(thread_pool& q)
      {
          while (optional<job_t> job = q.dequeue())
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
          _queue.push_back(job);

          cv.notify_one();
      }

      bool is_idle() const // warning, not overly useful, since a new job might
                           // be queued immediately after retrieving this state
      {
          lock_guard<mutex> lk(mx);
          return _queue.empty();
      }

      // This one is more useful, because the lock is transferred to the
      // caller, so the caller can rely on the queue to stay empty until it
      // unlocks
      unique_lock<mutex> wait_idle() const
      {
          unique_lock<mutex> lock(mx);

          namespace phx = boost::phoenix;
          cv.wait(lock, phx::empty(phx::ref(_queue)));

          return unique_lock<mutex>(*lock.release(), boost::adopt_lock);
      }

      optional<job_t> dequeue() 
      {
          unique_lock<mutex> lk(mx);
          namespace phx = boost::phoenix;

          cv.wait(lk, phx::ref(shutdown) || !phx::empty(phx::ref(_queue)));

          if (_queue.empty())
              return none;

          job_t job = _queue.front();
          _queue.pop_front();

          return job;
      }

      ~thread_pool()
      {
          shutdown = true;
          {
              lock_guard<mutex> lk(mx);
              cv.notify_all();
          }

          {
              // just as a demo, this is actually redundant:
              unique_lock<mutex> lock = wait_idle();
          }

          // threads would already only exit after work is completed
          pool.join_all();
      }
};

static const size_t bignumber = 1 << 10;

class myClass 
{
    thread_pool pool; // uses 1 thread per core

  public:
    bool busy() const 
    {
        return !pool.is_idle();
    }

    void launch_jobs()
    {
        std::cout << "enqueuing jobs... " << std::flush;
        for(size_t i=0; i<bignumber; ++i)
        {
            for(int j=0; j<2; ++j) {
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
    instance.launch_jobs();

    size_t last = 0;
    while (instance.busy())
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        if ((counter >> 4u) > last)
        {
            std::cout << "Progress: " << counter << "/" << (bignumber*2) << "\n";
            last = counter >> 4u;
        }
    }
}
