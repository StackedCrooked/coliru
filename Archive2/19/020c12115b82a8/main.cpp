#include <future>
#include <iostream>

int main()
{
    using namespace std::literals::chrono_literals;
    // vv if you forget this you likely have a bug
    /* auto async_is_stupid = */ std::async(std::launch::async, [] {
        std::this_thread::sleep_for(1s);
        std::cout << "pong\n" << std::flush;
    });
    std::cout << "ping\n" << std::flush;
}