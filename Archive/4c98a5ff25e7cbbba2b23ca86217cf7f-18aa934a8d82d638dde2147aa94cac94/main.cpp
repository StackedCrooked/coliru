#include "stm.hpp"
#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
#include <unistd.h>

class Test
{    
private:
    stm::shared<int> first;
    stm::shared<int> second;
    stm::shared<int> sum; // sum must *always* be equal to first + second!

public:
    void increment_first()
    {
        stm::atomic<void>(std::bind(&Test::do_increment_first, this, std::placeholders::_1));
    }
    
    void increment_second()
    {
        stm::atomic<void>(std::bind(&Test::do_increment_second, this, std::placeholders::_1));
    }
    
    typedef std::tuple<int, int, int> Snapshot;
    
    Snapshot get_snapshot() const
    {
        return stm::atomic<Snapshot>([this](stm::transaction & tx) {
            return std::make_tuple(first.open_r(tx), second.open_r(tx), sum.open_r(tx));
        });
    }
    
private:
    void do_increment_first(stm::transaction& tx)
    {        
        first.open_rw(tx)++;
        sum.open_rw(tx)++;
    };
    
    void do_increment_second(stm::transaction& tx)
    {        
        second.open_rw(tx)++;
        sum.open_rw(tx)++;
    };
};

int main()
{   
    Test test;
    
    std::atomic<bool> quit{};
    
    std::thread t1([&](){
        while (!quit) {
            test.increment_first();
        }
    });
    
    std::thread t2([&](){
        while (!quit) {
            test.increment_second();
        }
    });
    
    std::thread t3([&](){
        while (!quit) {
            auto snapshot = test.get_snapshot();
            std::cout << "Snapshot: " << std::get<0>(snapshot) << ", " << std::get<1>(snapshot) << ", sum: " << std::get<2>(snapshot) << std::endl;
            assert(std::get<0> + std::get<1> == std::get<2>);
        }
    });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    quit = true;
    t1.join();
    t2.join();
    t3.join();
}
