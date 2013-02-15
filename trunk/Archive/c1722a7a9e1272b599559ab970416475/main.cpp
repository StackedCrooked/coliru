#include "Poco/Stopwatch.h"
#include <deque>
#include <iostream>
#include <vector>

int main()
{
    {
        Poco::Stopwatch s;
        s.start();
        std::vector<unsigned> v;
        for (unsigned i = 0; i != 10000; ++i)
        {
            v.push_back(i);        
        }
        std::cout << "Vector took " << s.elapsed() << " microseconds" << std::endl;
    }
    {
        Poco::Stopwatch s;
        s.start();
        std::deque<unsigned> d;
        for (unsigned i = 0; i != 10000; ++i)
        {
            d.push_back(i);        
        }
        std::cout << "Deque took " << s.elapsed() << " microseconds" << std::endl;
    }
    
    std::cout << "Warmup completed." << std::endl;
    
    
    {
        Poco::Stopwatch s;
        s.start();
        std::vector<unsigned> v;
        for (unsigned i = 0; i != 10000; ++i)
        {
            v.push_back(i);        
        }
        std::cout << "Vector took " << s.elapsed() << " microseconds" << std::endl;
    }
    {
        Poco::Stopwatch s;
        s.start();
        std::deque<unsigned> d;
        for (unsigned i = 0; i != 10000; ++i)
        {
            d.push_back(i);        
        }
        std::cout << "Deque took " << s.elapsed() << " microseconds" << std::endl;
    }
}

