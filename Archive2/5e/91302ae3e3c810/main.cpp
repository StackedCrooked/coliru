#include <boost/thread/future.hpp>

void callback_function()
{
    std::cout << "Wait is called and promise not ready yet" << std::endl;
}

int main()
{
    boost::promise<std::string> promise;
    boost::unique_future<std::string> fut = promise.get_future();
    promise.set_wait_callback(boost::bind(callback_function));

    boost::async([&]{ sleep(2); promise.set_value("test"); });
    sleep(1);
    std::cout << fut.get();
}
