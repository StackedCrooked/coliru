#include <boost/any.hpp>
#include <boost/signals2/signal.hpp>
#include <iostream>
#include <string>

struct ip_stats_t { 
    std::string canary;
};

std::map<uint32_t, boost::any> _event_map;

template<typename... Args> using Sig = boost::signals2::signal<void(Args...)>;

template<typename... Args>
void emit(uint32_t event, Args... args) {
    if (_event_map.find(event) == _event_map.end())
        return;

    try {
        Sig<Args...> *sig = boost::any_cast<Sig<Args...> *>(_event_map[event]);
        
        (*sig)(args...);
    }
    catch (boost::bad_any_cast &e) {
        std::cerr << "Caught instance of boost::bad_any_cast: " << e.what();
        abort();
    }
}

int main()
{
    Sig<int, double> sig1;
    Sig<ip_stats_t&> sig2;

    sig1.connect([](int i, double d) { std::cout << "Sig1 handler: i = " << i << ", d = " << d << "\n"; });
    sig2.connect([](ip_stats_t& v)   { std::cout << "Sig2 handler: canary = " << v.canary << "\n"; });

    _event_map[1] = &sig1;
    _event_map[2] = &sig2;

    emit<int, double>(1, 42, 3.14);

    ip_stats_t instance { "Hello world" }, *ptr = &instance;

    emit<ip_stats_t&>(2, *ptr);
}
