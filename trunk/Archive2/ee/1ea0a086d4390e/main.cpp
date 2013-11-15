#include <chrono>
#include <thread>

template <typename T, typename Denom>
void my_function(bool work_really_hard, std::chrono::duration<T, Denom> timeout)
{
    // Do stuff, until timeout is reached.
    std::this_thread::sleep_for(timeout);
}

int main()
{
    my_function(true, std::chrono::milliseconds(100));
    my_function(true, std::chrono::seconds(2));
}
