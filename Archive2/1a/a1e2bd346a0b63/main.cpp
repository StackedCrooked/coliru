#ifndef HEADER_GUARD_CUSTOM_THREADPOOL_HPP
#define HEADER_GUARD_CUSTOM_THREADPOOL_HPP
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

namespace custom {
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
}

#endif // HEADER_GUARD_CUSTOM_THREADPOOL_HPP

#include <boost/asio.hpp>

namespace a = boost::asio;
using error = boost::system::error_code;

void timer_loop(a::deadline_timer& tim, custom::thread_pool& pool) {
    static boost::atomic_int count(0);

    tim.expires_from_now(boost::posix_time::milliseconds(10));
    tim.async_wait([&](error ec) {
        if (!ec && (++count < 100)) {
            int id = count;

            pool.enqueue([id] { 
                std::cout << "timer callback " << id << " started on thread " << boost::this_thread::get_id() << "\n";
                boost::this_thread::sleep_for(boost::chrono::milliseconds(rand()%1000));
                std::cout << "timer callback " << id << " completed\n";
            });

            std::cout << "Job " << id << " enqueued" << "\n";
            timer_loop(tim, pool);
        }
    });
}

int main()
{
    a::io_service svc;
    a::deadline_timer tim(svc);
    custom::thread_pool pool;

    timer_loop(tim, pool);

    svc.run();
}
