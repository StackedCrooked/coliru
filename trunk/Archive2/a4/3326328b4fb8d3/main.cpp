#include <functional>
#include <string>
#include <thread>
#include <iostream>


namespace Crooked {
namespace Stack {


//! Wrapper for std::thread which joins on destruction.
class Thread
{
public:
    template<typename F>
    Thread(const std::string& name, F&& f) :
        thread_([=](F&& f){ // should probably use packaged_task here
            try { f(); }
            catch (const std::exception& exc) { std::cerr << "Thread caught " << exc.what(); }
        }, std::forward<F>(f)),
        name_(name)
    {
    }
    
    ~Thread()
    {
        join();
    }
    
    void join()
    {
        if (thread_.joinable())
        {
            thread_.join();
        }
    }

private:
    std::thread thread_;
    std::string name_;
};


} } // namespace Crooked::Stack



int main()
{
    Crooked::Stack::Thread thread{ "my-thread", []{ std::cout << "HI" << std::endl; } };
}
