// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

class Test
{
  public:
    void foo()
    {
        auto fou = std::bind(&Test::bar, this, 3);
        auto fou2 = std::bind([&](){
                bar(4);
            
            });
        
        fou();
        fou2();
    }
    
    void bar(int value)
    {
     std::cout << value << std::endl;   
    }
  
};

int main ()
{
    Test test;
    
    test.foo();


    return 0;
}