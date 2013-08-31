#include <iostream>
#include <thread>
#include <condition_variable>


int main()
{
    std::mutex pingStartMutex;
    std::condition_variable pingStartCv;
    bool pingStarted = false;

    std::mutex pongStartMutex;
    std::condition_variable pongStartCv;
    bool pongStarted = false;
    
    std::mutex pingMutex;
    std::condition_variable pingCv;
    
    
    std::thread ping([&]()
    {
        //Notify about start
        {
            std::lock_guard<std::mutex> locker(pingStartMutex);
            pingStartCv.notify_one();
        }
         
        std::unique_lock<std::mutex> locker(pingMutex);
        pingCv.wait(locker);
            
    });

    std::thread pong([&]()
    {
        //Notify about start
        {
            std::lock_guard<std::mutex> locker(pongStartMutex);
            pongStartCv.notify_one();
        }
    });
    
    
    //Wait for ping start
    {
        std::unique_lock<std::mutex> locker(pingStartMutex);
        while (!pingStarted)
        {
            pingStartCv.wait(locker);
        }
    }
    
    
    //Wait for pong start
    {
        std::unique_lock<std::mutex> locker(pongStartMutex);
        while (!pongStarted)
        {
            pongStartCv.wait(locker);
        }
    }

    //Send signal to ping 
    {
        std::lock_guard<std::mutex> locker(pingMutex);
        pingCv.notify_one();
    }
    
    ping.join();
    pong.join();

}