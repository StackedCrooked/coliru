#include <iostream>
#include <string>


template<typename T>
struct Wrap
{    
    template<typename T1>
    Wrap(T1& t1) : obj(t1)
    {
        std::cout << "Wrap" << std::endl;
    }
    
    T obj;
};


int main()
{    
    std::cout << "Begin" << std::endl;
    Wrap<int> wrap(std::string());
    std::cout << "End" << std::endl;
}