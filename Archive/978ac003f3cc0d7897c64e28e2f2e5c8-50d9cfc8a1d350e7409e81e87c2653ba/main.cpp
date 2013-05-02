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
        mStatus.store(PROCESSED);
    }

    bool startProcessing()
    {
        Status expected = PROCESSING;
        return mStatus.compare_exchange_strong(expected, READY);
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
    
    if (task.startProcessing())
        task.exec();
        
    if (task.isProcessed())
        std::cout << ans << std::endl;
    
    return 0;
}
