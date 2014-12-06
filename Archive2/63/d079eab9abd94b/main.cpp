#include <boost/thread/future.hpp>

void callback_test()
{
   std::cout << "callback_test" << std::endl;
}

void promise_task(boost::promise<std::string> & promise)
{
  std::cout << "promise_task" << std::endl;
  sleep (2);
  promise.set_value("PROMISE");

}

void future_task(boost::unique_future<std::string> & future)
{
  std::cout << "futute_task" << std::endl;
  std::cout << future.get() << std::endl;
  callback_test();
}

void promise_and_future_task(boost::promise<std::string> & promise, boost::unique_future<std::string> & future)
{
  boost::thread promise_task_(&promise_task,
        boost::ref(promise));

  boost::thread future_task_(&future_task,
        boost::ref(future));
}

void do_other_main_task()
{
  sleep(5);
}

int main()
{
  boost::promise<std::string> promise;
  boost::unique_future<std::string> fut = promise.get_future();
//  promise.set_wait_callback(boost::bind(callback_test));
  boost::thread task(
      &promise_and_future_task,
      boost::ref(promise),
      boost::ref(fut));

  std::cout << "MAIN THREAD" << std::endl;

  do_other_main_task();
  return 0;
}
