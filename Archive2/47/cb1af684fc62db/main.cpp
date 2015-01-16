#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

////////////////////
// Diet Boost:
template <typename T> using optional = std::unique_ptr<T>; // poor man's optional
static const std::nullptr_t none {};

struct thread_group final { // poor man's thread_group
    template <typename... A> std::thread& create_thread(A&&... args) {
        _v.emplace_back(std::forward<A>(args)...);
        return _v.back();
    }

    ~thread_group() { join_all(); } // http://www.open-std.org/Jtc1/sc22/wg21/docs/papers/2008/n2802.html
    void join_all() {
        for (auto &t : _v)
            if (t.joinable()) t.join();
    }
  private:
    std::list<std::thread> _v;
};
// End Diet
////////////////////


std::atomic_size_t counter(0ul);

class thread_pool
{
  private:
      std::mutex mx;
      std::condition_variable cv;

      typedef std::function<void()> job_t;
      std::deque<job_t> _queue;

      thread_group pool;

      std::atomic_bool shutdown;
      void worker_thread() {
          while (auto job = dequeue())
              (*job)();
      }

  public:
      thread_pool() : shutdown(false) {
          for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i)
              pool.create_thread(&thread_pool::worker_thread, this);
      }

      void enqueue(job_t job)
      {
          std::lock_guard<std::mutex> lk(mx);
          _queue.push_back(std::move(job));

          cv.notify_one();
      }

      optional<job_t> dequeue()
      {
          std::unique_lock<std::mutex> lk(mx);

          cv.wait(lk, [&] { return shutdown | !_queue.empty(); });

          if (_queue.empty())
              return none;

          auto job = std::move(_queue.front());
          _queue.pop_front();

          return optional<job_t>(new job_t(std::move(job)));
      }

      ~thread_pool()
      {
          shutdown = true;
          {
              std::lock_guard<std::mutex> lk(mx);
              cv.notify_all();
          }

          pool.join_all();
      }
};

#include <iostream>

static constexpr size_t bignumber = 1 << 20;

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
                pool.enqueue(std::bind(&myClass::myFunction, this, j, i));
            }
        }
        std::cout << "done\n";
    }

  private:
    void myFunction(int i, int j)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if ((counter >> 4u) > last)
        {
            std::cout << "Progress: " << counter << "/" << (bignumber*2) << "\n";
            last = counter >> 4u;
        }
    }
}
