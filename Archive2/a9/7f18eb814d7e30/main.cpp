#include <iostream>
#include <functional>
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

struct erased_connection
{
    
public:
    
    erased_connection(bs2::connection c)
    {
        auto sc = std::make_shared<bs2::connection>(std::move(c));
        disconnector = [sc] { sc->disconnect(); };
    }
    
    erased_connection(std::function<void()> disconnector)
        : disconnector{disconnector}
    {
    }

    erased_connection(erased_connection&& rhs)
        : disconnector{std::move(rhs.disconnector)}
    {
        rhs.disconnector = nullptr;
    }

    erased_connection& operator = (erased_connection&& rhs)
    {
        disconnector = std::move(rhs.disconnector);
        rhs.disconnector = nullptr;
        return *this;
    }
    
    void disconnect()
    {
        disconnector();
    }
    
    ~erased_connection()
    {
        disconnector();
    }
    
private:

    std::function<void()> disconnector;
    
};

int main()
{  
    bs2::signal<void()> s;
    
    erased_connection c = s.connect([] { std::cout << "Hello!" << std::endl; });
    
    s(); // Will cause printing
    
    c.disconnect();
    
    s(); // Will not cause printing
}