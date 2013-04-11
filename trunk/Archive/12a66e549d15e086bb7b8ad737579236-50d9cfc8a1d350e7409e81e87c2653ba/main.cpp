#include <functional>
#include <future>
#include <iostream>
#include <thread>

void http_get(const std::string & url, const std::function<void(std::string)> & callback)
{
    callback("404: " + url); // dummy result
}

std::future<std::string> http_get(const std::string & url)
{
    auto shared_promise = std::make_shared<std::promise<std::string>>();
    http_get(url, [=](const std::string & result) {
        shared_promise->set_value(result);
    });
    return shared_promise->get_future();
}

int main()
{
    std::cout << http_get("abc").get();
}