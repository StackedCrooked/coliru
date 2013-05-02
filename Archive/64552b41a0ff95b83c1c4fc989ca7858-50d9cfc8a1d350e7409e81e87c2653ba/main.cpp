#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <atomic>

namespace lockfree {

class Task{
public:
    enum Status
    {
        READY,
        PROCESSING,
        PROCESSED
    };

    Task()
    {
        mStatus = READY;
    }
    
    virtual ~Task()
    {
    }

    virtual void run() = 0;
    
    void exec()
    {
        run();
        mStatus = PROCESSED;
    }

    bool startProcessing()
    {
        Status expected = PROCESSING;
        return mStatus.compare_exchange_strong(expected, READY);
    }

private:
    std::atomic<Status> mStatus;
};

} // namespace

class MyTask : public lockfree::Task
{
    public:
        void run()
        {
            std::cout << "Hello World\n";
        }
};

int main()
{
    MyTask task;
    
    return 0;
}
