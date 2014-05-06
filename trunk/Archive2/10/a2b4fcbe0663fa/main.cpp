#include <deque>
#include <iostream>
#include <memory>
#include <string>

template<typename F>
struct ScopeGuard
{
    ScopeGuard(F&& f) :
        f(std::forward<F>(f)),
        armed(true)
    {
    }
    
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    
    ScopeGuard(ScopeGuard&&) = default;
    ScopeGuard& operator=(ScopeGuard&&) = default;
    
    ~ScopeGuard()
    {
        if (armed)
        {
            f();
        }
    }
    
    void disarm()
    {
        armed = false;
    }
    
private:
    F f;
    bool armed;
};


template<typename F>
ScopeGuard<F> make_scope_guard(F&& f)
{
    return ScopeGuard<F>(std::forward<F>(f));
}

 


std::deque<std::string> pending_items = { "A", "B", "C", "D", "E" };
std::deque<std::string> sent_items;


std::string steal_one()
{   
    auto item = std::move(pending_items.front());
    pending_items.pop_front();
    sent_items.push_back(item);
    return item;
}


void send_item(const std::string& s)
{
    static int i = 0;
    if (i++ % 3 == 0)
    {
        throw std::runtime_error("Send fail: " + s);
    }
    std::cout << "Send OK: " << s << std::endl;
}


void send_one()
{   
    auto item = steal_one();
    
    auto rollback = make_scope_guard([]{
        pending_items.push_front(sent_items.back());
        sent_items.pop_back();
    });
    
    send_item(item);
    
    rollback.disarm();
}


void send_all()
{
    while (!pending_items.empty())
    {
        try
        {
            send_one();
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}


int main()
{
    send_all();
}