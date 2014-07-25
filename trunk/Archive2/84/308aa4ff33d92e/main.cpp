#include <iostream>

#include <memory>

#include <string>
#include <sstream>

#include <thread>
#include <future>
#include <mutex>

#include <vector>

template < typename T >
struct Monitor
{
private:
    mutable T t_;
    mutable std::mutex m_;

public:
    Monitor(const T& t)
    : t_(t)
    {   
    }
    template < typename F >
    void operator() (F f) const
    { 
        std::lock_guard<std::mutex> _{m_}; 
        return f(t_);
    }

};


Monitor<std::string> s( std::string("start\n") );

int main()
{
    using futures_t = std::vector<std::future<void>>;
    futures_t futures;
    futures.reserve(5);
    for ( int i =0 ; i < 5; ++i )
    {
        futures[i] = std::async(std::launch::async,
            [&]()
            {
                s(
                    [=](std::string& s)
                    {
                        s += std::to_string(i) + " " + std::to_string(i);
                        s += "\n";
                    }
                );
                
                s(
                    [=](const std::string& s)
                    {
                        std::cout << s;    
                    }
                );
                
                
            }
            
        );    
    }
    std::cout << "waiting...\n";
    for( auto const & each : futures)
        each.wait();
    std::cout << "done...\n";
    return 0;
}