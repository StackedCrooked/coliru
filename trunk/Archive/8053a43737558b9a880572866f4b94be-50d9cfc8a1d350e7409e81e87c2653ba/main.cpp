#include <iostream>

#include <thread>
#include <condition_variable>
#include <mutex>

auto const n = 3;

bool done = false;
bool need_to_pong = false;

std::mutex m;

std::condition_variable ping_cond;
std::condition_variable pong_cond;

void ping()
{           
   std::unique_lock<std::mutex> lock(m);
   
   pong_cond.wait(lock);
    
    for(int i = 0; i < n; ++ i)
    {   
        std::cout << "Ping!\n";
        
        need_to_pong = true;
        
        ping_cond.notify_one();
        
        pong_cond.wait(lock);
    }
    
    done = true;
    
    ping_cond.notify_one();
}

void pong()
{  
    std::unique_lock<std::mutex> lock(m);
    pong_cond.notify_one();
    
    while(!done)
    {
        ping_cond.wait(lock);
        
        if(need_to_pong)
        {
            std::cout << "Pong!\n";
            need_to_pong = false;
        }
        
        pong_cond.notify_one();
    }
}

int main()
{
    std::cout << "Ready… Set… Go!\n";
    
    std::thread Ping(ping);
    std::thread Pong(pong);
    
    Ping.join();
    Pong.join();
    
    std::cout << "Done!\n";
    
    return 0;
}
