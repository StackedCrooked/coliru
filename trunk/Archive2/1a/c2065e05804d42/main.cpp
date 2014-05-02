#include <boost/config/warning_disable.hpp>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct T
{
    std::string name;
    std::vector<T> others;
    
    T() {};
    ~T() {};
    
   // T(T&& rhs) : name(std::move(rhs.name)) {};
    T(const std::string& n) : name(n)
    {
        others = std::vector<T>(10);
    };
    

    
};

int main()
{    
    T t1("t1");
    T t2("t2");
        
    int rep = 100000;

    std::cout << "Starting..." << std::endl;
    
    boost::timer::auto_cpu_timer timer;
    for(int i = 0; i < rep; ++i)
    {
        t2 = std::move(t1);
        t1 = std::move(t2);
    }
    
    timer.stop();
    timer.report();
    
    std::cout << "Done..." << std::endl;
    std::cout << "  T1: " << t1.name << std::endl;
    std::cout << "  T2: " << t2.name << std::endl;
}