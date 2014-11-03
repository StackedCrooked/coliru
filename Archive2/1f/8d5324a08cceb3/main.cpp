#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/phoenix.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <string>
#include <deque>

using namespace boost;

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
          while (optional<job_t> job = q.dequeue())
              (*job)();
      }

  public:
      thread_pool() : shutdown(false) {
          //LOG_INFO_MESSAGE << "Number of possible Threads: " << boost::thread::hardware_concurrency() << std::endl;
          for (unsigned i = 0; i < boost::thread::hardware_concurrency(); ++i){
              pool.create_thread(bind(worker_thread, ref(*this)));
          }
      }

      void enqueue(job_t job)
      {
          lock_guard<mutex> lk(mx);
          _queue.push_back(job);

          cv.notify_one();
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

      void WaitTillAllJobsAreDone(){
          shutdown = true;
          {
              lock_guard<mutex> lk(mx);
              cv.notify_all();
          }

          pool.join_all();
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

struct ClassB {
    ClassB() : stuff(new int[256]) { }

    std::unique_ptr<int[]> stuff; // could be other resources, such as threads, filehandles etc.
};

class Foo
{
  public: 
    Foo(std::vector<boost::shared_ptr<ClassB> > data)
        : m_data(data),
          m_maxDepth(5)
    {

    }

    void initializateThreads() {
        thread_pool threadPool;
        std::vector<std::vector<double> > result(m_data.size());
        std::vector<std::vector<double> >::iterator it = result.begin();

        for (auto d : m_data) {
            threadPool.enqueue(boost::bind(&Foo::Work, this, d, boost::ref(*it), 1));
            ++it;
        }
        
        threadPool.WaitTillAllJobsAreDone();

        // do something with results;
    }

    void Work(boost::shared_ptr<ClassB> ptr, std::vector<double>& resultThread, int currentDepth)
    {
        if (currentDepth > m_maxDepth)
            return;

        std::cout << "." << std::flush;

        // do some calculation with ptr and add it to resultThread
        resultThread.push_back(42);

        Work(ptr, resultThread, (currentDepth + 1));
    }

    std::vector<boost::shared_ptr<ClassB> > m_data;
    int m_maxDepth;
};

int main()
{
    std::vector<boost::shared_ptr<ClassB>> v;
    std::generate_n(std::back_inserter(v), 500, []{return make_shared<ClassB>();});
    Foo foo(v);

    foo.initializateThreads();
}
