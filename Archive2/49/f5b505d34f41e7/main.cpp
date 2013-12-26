#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>

int fib(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    return fib(x-1)+fib(x-2);
}

void doSomething(int value)
{
  std::cout << "doSomething(): " << fib(value) << std::endl;
}

void doSomethingElse(int value)
{
  std::cout << "doSomethingElse(): " << value+value << std::endl;
}

int main(int argc, char** argv)
{
  // create asio ioservice and threadgroup for the pool
  boost::asio::io_service ioService;
  boost::thread_group threadpool;

  // Add worker threads to threadpool
  for(int i = 0; i < 5; ++i)
  {
    threadpool.create_thread(
      boost::bind(&boost::asio::io_service::run, &ioService));  
  }

  // post work to the ioservice
  ioService.post(boost::bind(doSomething, 40));
  ioService.post(boost::bind(doSomethingElse, 3));

  // run the tasks and return, if all queued work is finished
  ioService.run();

  // join all threads of the group
  threadpool.join_all();
}