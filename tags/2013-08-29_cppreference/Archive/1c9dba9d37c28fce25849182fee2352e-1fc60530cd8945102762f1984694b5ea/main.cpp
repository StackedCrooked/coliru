#include <boost/thread.hpp>
#include <functional>
#include <future>
#include <iostream>
#include <vector>


using Callback = std::function<void(std::string)>;
std::vector<boost::thread> threads;

void http_get(const std::string & url, const Callback & callback)
{
    threads.emplace_back([=]() {
        try {
            callback("<html><body>got " + url + "</body></html>");
        } catch (const std::exception & exc) {
            std::cout << "http_get: " << exc.what() << std::endl;
        }
    });
}

std::future<std::string> callback2future(const std::string & url)
{
    auto shared_promise = std::make_shared<std::promise<std::string>>();
    auto result = shared_promise->get_future();
    http_get(url, [=](const std::string & result) {
        shared_promise->set_value(result);
    });
    return result;
}


void callback2future2callback(const std::string & url, const Callback & cb)
{
    threads.emplace_back([=]() {
        try {
            cb(callback2future(url).get());
        } catch (const std::exception & exc) {
            std::cout << "callback2future2callback: " << exc.what() << std::endl;
        }
    });
}


int main()
{
    callback2future2callback("c", [](const std::string & result) {
        std::cout << result << std::endl;
    });
    
    for (auto & t : threads)
    {
        t.join();
    }
}
