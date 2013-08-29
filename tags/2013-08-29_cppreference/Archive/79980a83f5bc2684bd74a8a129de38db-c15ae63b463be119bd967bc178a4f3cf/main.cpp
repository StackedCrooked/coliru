#include <iostream>
#include <future>


// http_get using a std::future
std::future<std::string> http_get(const std::string& url);


// http_get using a callback
template<typename Callback>
std::future<void> http_get(const std::string& url, Callback callback)
{
    return std::async(std::launch::async, [=] {
        callback(http_get(url).get());
    });
}


int main()
{    
    // using std::future
    std::future<std::string> page = http_get("google.com");
    std::cout << page.get() << std::endl;
    
    
    // using callback
    auto result = http_get("google.com", [](const std::string& page) {
        std::cout << page << std::endl;
    });
    result.wait();
}