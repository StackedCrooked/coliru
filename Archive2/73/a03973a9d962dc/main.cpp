#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

#include <condition_variable>
#include <iostream>
#include <mutex>

const int THREAD_POOL_SIZE = 2;

std::condition_variable g_cv;
std::mutex g_cv_mutex;
bool g_answer_ready;

void foo()
{
  std::cout << "foo \n";
  std::unique_lock<std::mutex> lock(g_cv_mutex);
  g_answer_ready = true;
  g_cv.notify_all();
}

int main()
{
  boost::asio::io_service io_service;

  for (int i = 0; i < 10; ++i)
  {
    std::auto_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(io_service));

    boost::thread_group threads;
    for (int i = 0; i < THREAD_POOL_SIZE; ++i)
    {
      threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
    }

    std::unique_lock<std::mutex> lock(g_cv_mutex);

    io_service.post(foo);

    g_answer_ready = false;
    g_cv.wait_for(lock, std::chrono::milliseconds(2000));

    if (!g_answer_ready)
    {
      std::cout << "timed_out \n";
    }

    io_service.stop();
    threads.join_all();
  }
}
