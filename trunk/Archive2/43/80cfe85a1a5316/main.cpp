#include <functional>
#include <chrono>
#include <future>
#include <cstdio>

class later
{
public:
    template <class callable, class... arguments>
    later(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async)
        {
            std::thread([after, task]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }).detach();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }

};

void test1(void)
{
    return;
}

void test2(int a)
{
    printf("%i\n", a);
    return;
}

int main()
{
    later later_test1(1000, false, &test1);
    later later_test2(1000, false, &test2, 101);

    return 0;
}