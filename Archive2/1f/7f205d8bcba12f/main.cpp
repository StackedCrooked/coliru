#include <memory>
#include <iostream>
#include <functional>
#include <vector>

int main()
{
    typedef std::function<void()> CallbackFunc;
    typedef std::shared_ptr<CallbackFunc> Callback;
    typedef std::weak_ptr<CallbackFunc> CallbackHandle;

    std::vector<CallbackHandle> callbacks;

    auto a = Callback(new CallbackFunc([]() { std::cout << "Hello, "; }));
    callbacks.emplace_back(a);

    {
        auto b = Callback(new CallbackFunc([]() { std::cout << "World"; }));
        callbacks.emplace_back(b);
    } // b no longer exists

    for (auto& c : callbacks)
    {
        if (auto spt = c.lock())
        {
            (*spt)();
        }
        else
        {
            std::cout << "expired.";
        }
    }

    return 0;
}