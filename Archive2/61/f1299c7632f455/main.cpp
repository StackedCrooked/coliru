#include <boost/thread/future.hpp>

void callback_function(boost::unique_future<std::string>& fut)
{
    std::cout << "Wait is called and promise not ready yet" << std::endl;
    std::cout << fut.get(); // oops recursion!
}

int main()
{
    boost::promise<std::string> promise;
    boost::unique_future<std::string> fut = promise.get_future();
    promise.set_wait_callback(boost::bind(callback_function, boost::ref(fut)));

    boost::async([&]{ sleep(3); promise.set_value("test"); });
    sleep(2);
    fut.get();
}
