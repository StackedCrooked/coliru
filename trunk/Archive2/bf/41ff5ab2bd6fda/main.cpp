#include <mutex>

struct once_flag {
    bool done = false;
    std::mutex mut;
};
template<typename Callable, typename... Args>
void call_once(once_flag &flag, Callable &&f, Args &&...args)
{
    std::lock_guard<std::mutex> lock(flag.mut);
    if(!flag.done)
    {
        f(args...);
        flag.done = true;
    }
}

#include <iostream>

int main()
{
    once_flag f;
    call_once(f, [](){std::cout << "hello world";});
    call_once(f, [](){std::cout << "hello world";});
}