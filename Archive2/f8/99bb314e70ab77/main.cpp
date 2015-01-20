#include <memory>
#include <iostream>
#include <mutex>
#include <future>

template<typename T>
class synchronized
{
public:
    synchronized(T&& obj) : _obj{std::move(obj)} { }
    
    template<typename F>
    void safe_invoke(F&& f)
    {
        std::lock_guard<std::mutex> lock{_m};
        f(_obj);
    }
    
private:
    T _obj;
    std::mutex _m;
};

int printer(synchronized<std::string>& s)
{
    auto total = 0;
   
    for (auto i = 0; i < 10000; ++i)
    {
        s.safe_invoke([&] (auto const& s)
        {
            total += s.size();
        });
    }
    
    return total;
}

void modifier(synchronized<std::string>& s)
{
    for (auto i = 0; i < 10000; ++i)
    {
        s.safe_invoke([&] (auto& s)
        {
            s = std::to_string(i * 5);
        });
    }
}

int main()
{
    synchronized<std::string> s{"Hello"};
    
    auto f1 = std::async(std::launch::async, printer, std::ref(s));
    
    auto f2 = std::async(std::launch::async, modifier, std::ref(s));

    std::cout << f1.get();
    
    f2.wait();
}