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
        mStatus.store(READY);
    }
    
    virtual ~Task()
    {
    }

    virtual void run() = 0;
    
    void exec()
    {
        run();
        mStatus.store(PROCESSED);
    }

    bool startProcessing()
    {
        Status expected = READY;
        return mStatus.compare_exchange_strong(expected, PROCESSING);
    }
    
    bool isProcessed() const
    {
          return PROCESSED && mStatus.load(); 
    }

private:
    std::atomic<Status> mStatus;
};

} // namespace

class MyTask : public lockfree::Task
{
    public:
    MyTask(int& a):
    a(a)
    {
    }
    
        void run()
        {
            //std::cout << "Hello World\n";
            a++;
        }
        
        private:
        int& a;
};

int main()
{
    int ans = 5;
    MyTask task(ans);
    
    std::cout << "Start\n";
    
    if (task.startProcessing())
    {
        std::cout << "startProcessing\n";
        task.exec();
    }
    
    if (task.isProcessed())
    {
        std::cout << "isProcessed\n";
        std::cout << ans << std::endl;
    }
    
    std::cout << "End\n";
    return 0;
}
