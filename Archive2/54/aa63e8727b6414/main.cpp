#include <chrono>
#include <iostream>
#include <thread>

class active_object
{
public:

    active_object() : m_thread(&active_object::thread_body, this) {}

    void thread_body()
    {
        std::cout << "Thread body just started" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Thread body about to end" << std::endl;
    }

private:
    std::thread m_thread;
};

int main()
{
    std::cout << "Started main, starting worker" << std::endl;
    
    active_object runner;
    
    std::cout << "Started worker" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
	return 0;
}