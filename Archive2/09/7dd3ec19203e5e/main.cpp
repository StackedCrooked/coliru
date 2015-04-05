#include <iostream>
#include <random>
#include <chrono>

struct a
{
    virtual void x()
    {
        std::cout << "a";   
    }
};

struct b : public a
{ 
    void x() override
    {
        std::cout << "b";
    }
};

int main()
{
    a myAinstance;
    b myBinstance;
    
    std::mt19937 mt;
    try
    {
        std::random_device rd; //might throw for Windows or so
        mt = std::mt19937(rd()); //shuffle the mersenne twister
    }
    catch(...)
    {
        //shuffle the mersenne twister
        mt = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
    }
    
    std::uniform_int_distribution<std::size_t> dist(0ULL, 1ULL);
    std::size_t result = dist(mt);
    
    std::cout << "Will run x() from " << ((result == 0ULL)?("a"):("b")) << " instance:\n";
    
    if(result == 0ULL)
        myAinstance.x();
    else
        myBinstance.x();
}