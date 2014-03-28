#include <mutex>

struct once_flag {
    bool done = false;
    std::recursive_mutex mut;
};
template<typename Callable, typename... Args>
void call_once(once_flag &flag, Callable &&f, Args &&...args)
{
    std::lock_guard<std::recursive_mutex> lock(flag.mut);
    if(!flag.done)
    {
        f(args...);
        flag.done = true;
    }
}

#include <iostream>

void foo(int p);

void bar(int p)
{
    static once_flag f;
    call_once(f, [p](){foo(p);});
}

void foo(int p)
{
    if(p < 42)
    {
        bar(p+1);
    }else
    {
        std::cout << "finished";
    }
}

int main()
{
    bar(0);
}