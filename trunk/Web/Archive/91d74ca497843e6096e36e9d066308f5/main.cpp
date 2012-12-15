#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>
#include <thread>


template<typename T>
class bridge
{    
public:
    std::string pop()
    {
        return async([this]() ->std::string {
            std::unique_lock<std::mutex> lck(mtx);
            mCond.wait(lck);
            if (mJobs.empty())
            {
                throw std::runtime_error("mJobs.empty");
            }
            auto result = mJobs.front();
            mJobs.pop_front();
            return result;
        }).wait();
    }
    
    void push(const std::string & job)
    {
        std::unique_lock<std::mutex> lck(mtx);
        mJobs.push_back(job);
        mJobs.notify_one();        
    }
    
private:
    std::condition_variable mCond;
    std::mutex mtx;
    std::deque<std::string> mJobs;
};


int main()
{
    bridge b;
    std::thread t1([&](){ std::cout << b.pop() << std::endl; });
    std::thread t2([&](){ std::cout << b.push("abc") << std::endl; });
    t2.join();
    t1.join();
}