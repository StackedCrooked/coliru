#include <functional>
#include <vector>

template<typename... Args>
struct event
{
    using handler_type = std::function<void(Args const&...)>;
    void add_handler(handler_type h) { _handlers.push_back(std::move(h)); }        
    void fire(Args const&... args) 
    { for (auto const& h : _handlers) { h(args...); } }
private:    
    std::vector<handler_type> _handlers;
};

#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    event<int> e1;
    e1.add_handler([] (int const& i) { std::cout << i << std::endl; });
    e1.fire(42);

    event<int, std::string, bool> e2;
    e2.add_handler([] (int const& i, std::string const& s, bool b) 
    { std::cout << i << " " << s << std::boolalpha << " " << b << std::endl; });
    e2.fire(42, "Hello", true);
}