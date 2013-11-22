#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>

using namespace std;

struct GameLoop
{
    atomic<bool> run;
    thread runThread;
    
    GameLoop() : run(true) {}

    void Run()
    {
        while (run)
        {
            std::cout << ".";
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        std::cout << "\nFinished!\n";
    }

    ~GameLoop()
    {
        run = false;
        if (runThread.joinable()) runThread.join();
    }
};

int main()
{
    {
        GameLoop loop;
        
        loop.runThread = thread(&GameLoop::Run, std::ref(loop));

        this_thread::sleep_for(chrono::milliseconds(2500));
    }
}