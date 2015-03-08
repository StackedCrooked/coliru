# include <chrono>
# include <iostream>
# include <thread>
# include <vector>
namespace Chrono = std::chrono;
using namespace std::literals::chrono_literals;

class ThreadPool
{
public:
    explicit ThreadPool() {
        createPool(2);
    }
    
    ~ThreadPool() {
        std::cout << std::this_thread::get_id()
                  << " - ~ThreadPool()." << std::endl;
        status_ = Status::finishing;
        for (auto & th : pool_)
            th.join();
    }
    
    void addTask() {}
private:
    enum class Status : unsigned char {
        performedTask, noTasks, finishing 
    };

    template <typename BaseDuration = Chrono::milliseconds,
              typename StepDuration = Chrono::microseconds>
    void createPool(std::size_t poolSize = std::thread::hardware_concurrency(),
        BaseDuration baseTimeout = 1ms, StepDuration timeoutStep = 10us);
        
    Status performTask() {
        return status_;
    }
        
    std::vector<std::thread> pool_;
    Status status_ = Status::noTasks;
};

template <typename BaseDuration, typename StepDuration>
void ThreadPool::createPool(const std::size_t poolSize,
      const BaseDuration baseTimeout, const StepDuration timeoutStep)
{
    pool_.reserve(poolSize);
    for (std::size_t i = 0; i < poolSize; ++i) {
        const auto timeout = baseTimeout + i * timeoutStep;
        pool_.emplace_back([this, timeout] {
            Status status;
            do {
                status = performTask();
                if (status == Status::noTasks) {
                    std::cout << std::this_thread::get_id()
                              << " - no tasks." << std::endl;
                    std::this_thread::sleep_for(timeout);
                }
            } while (status != Status::finishing);
            std::cout << std::this_thread::get_id()
                      << " - finishing." << std::endl;
        });
    }
}

int main()
{
    ThreadPool threadPool;
}
