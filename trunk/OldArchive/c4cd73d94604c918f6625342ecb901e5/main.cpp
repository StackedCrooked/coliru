#include <condition_variable>
#include <deque>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>


class bridge
{    
public:
    std::string wait()
    {
        return std::async([this]() ->std::string {
            std::unique_lock<std::mutex> lck(mtx);
            mCond.wait(lck);
            if (mJobs.empty())
            {
                throw std::runtime_error("mJobs.empty");
            }
            auto result = mJobs.front();
            mJobs.pop_front();
            return result;
        }).get();
    }
    
    void update(const std::string & job)
    {
        std::unique_lock<std::mutex> lck(mtx);
        mJobs.push_back(job);
        mCond.notify_one();
    }
    
private:
    mutable std::condition_variable mCond;
    mutable std::mutex mtx;
    std::deque<std::string> mJobs;
};


int main()
{
    bridge b;
    std::thread t1([&](){ std::cout << b.wait() << std::endl; });
    std::thread t2([&](){ b.update("abc"); });
    t2.join();
    t1.join();
}