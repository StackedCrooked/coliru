// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unordered_map>
#include <utility>

enum class Prout
{
    Banane
};

Prout getABC()
{
    return Prout::Banane;
}

class Test
{
  public:
  
    void foo()
    {
        map_[static_cast<std::underlying_type<Prout>::type>(getABC())] =  "Banane flambée";
    }
    
    std::string bar()
    {
        return map_[static_cast<std::underlying_type<Prout>::type>(getABC())];
    }
    
    private:
        std::unordered_map<std::underlying_type<Prout>::type, std::string> map_;
  
};

int main ()
{
    Test test;
    
    test.foo();
    
    std::cout << test.bar() << std::endl;


    return 0;
}