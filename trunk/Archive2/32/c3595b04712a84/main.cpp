#include <string>
#include <sstream>
#include <thread>
#include <iostream>


struct LogItem : std::stringstream { ~LogItem() { std::cout << str() << std::endl; } };
#define LOG(Level) if (0) {} else LogItem{}



// Convenience wrapper for std::thread
// - joins on destruction (no terminate if joinable)
// - catches any exceptions and logs them (instead of terminate) (=> this one may not be desirable)
// - has a name (which is very helpful when reading the log files)
class Thread
{
public:
    template<typename F>
    Thread(const std::string& name, F f) :
        thread_([=]{
            try {
                f();
            } catch (const std::exception& exc) {
                LOG(Error) << "Thread " << name << ": caught exception: " << exc.what() << ". Thread will now exit.";
            }
        }),
        name(name)
    {
        LOG(Info) << "Created thread " << name;
    }

    ~Thread()
    {
        join();
        LOG(Info) << "Destroying thread " << name;
    }

    void join()
    {
        if (thread_.joinable())
        {
            LOG(Info) << "Joining thread " << name;
            thread_.join();
            LOG(Info) << "Joined thread " << name;
        }
    }

private:
    std::thread thread_;
    std::string name;
};



int main()
{
    
    Thread main("Main", [=]{
        LOG(Info) << "It's nice being main.";
    });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
}