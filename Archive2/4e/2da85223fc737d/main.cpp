#include <future>
#include <chrono>
#include <iostream>

struct State
{
    void load() { 
        std::cout << "working\n";
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << "done\n";
    }
};

struct Object
{
    /* A method in a loop */
    bool run()
    {
        switch(future.wait_for(std::chrono::milliseconds(100)))
        {
            case std::future_status::ready:
                {
                    /* do something */
                }
                return false;
            case std::future_status::timeout:
                {
                    /* draw interface, manage event, … */
                }
            case std::future_status::deferred:
            default:
                return true;
        }
    }

    Object()  { init(); }
    ~Object() { if (future.valid()) future.wait(); }
  private:
    void init()
    {
        future = std::async(std::launch::async, &State::load, &stateInstance);
    }

    State stateInstance;
    std::future<void> future;
};

int main()
{
    Object test;

    while (test.run());
}
