#include <future>


int main()
{
    std::promise<int> prom;
    auto fut = prom.get_future();
    std::async(std::launch::async, [&]{ prom.set_value(0); });
    return fut.get();
}

