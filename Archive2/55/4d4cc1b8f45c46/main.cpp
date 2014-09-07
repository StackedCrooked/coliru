#include <atomic>
#include <vector>
#include <iterator>
#include <iostream>
#include <queue>
#include <chrono>
#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <boost/optional.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct PriorityLevel {
    PriorityLevel(
        const int32_t& rChannel = -1,
        const char priority = 'Z',
        const boost::optional<int32_t>& rSequenceNum = boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriority(priority)
        , mSequenceNum(rSequenceNum)
    {}

    // comparator that orders the elements in the priority_queue<PriorityInfo>
    inline bool operator<(const PriorityLevel& rhs) const {
        // compare tuples in left to right order using < operator
        // note in order to consider lower values higher priority
        // I had to reverse the intuitive < for a > comparison here
        return std::tie(mChannel, mPriority, mSequenceNum) >
            std::tie(rhs.mChannel, rhs.mPriority, rhs.mSequenceNum);
    }

    // stream friendly struct
    inline friend std::ostream& operator << (std::ostream& os, const PriorityLevel& rValue) {
        std::string sequenceInfo;
        if (rValue.mSequenceNum) {
            sequenceInfo = std::string(", sequence[") + 
                std::to_string(rValue.mSequenceNum.get()) + "]";
        }
        os  << "channel[" << rValue.mChannel
            << "], priority[" << rValue.mPriority << "]" << sequenceInfo;
        return os;
    }
    // the 3 fields from the szPriorityLevel field in the ModuleNameTable
    int32_t mChannel;
    char mPriority;
    boost::optional<int32_t> mSequenceNum;
};

template<typename T>
class UtlThreadSafePriorityQueue {
private:
    mutable std::mutex mut;
    std::priority_queue<T> data_queue;
    std::condition_variable data_cond;
    std::size_t capacity;
    std::atomic<bool> shutdownFlag;
public:
    explicit UtlThreadSafePriorityQueue(const size_t& rCapacity =
        std::numeric_limits<std::size_t>::max())
        : mut()
        , data_queue()
        , data_cond()
        , capacity(rCapacity)
        , shutdownFlag(false)
    {}

    UtlThreadSafePriorityQueue(UtlThreadSafePriorityQueue const& rhs) {
        std::lock_guard<std::mutex> lk(rhs.mut);
        data_queue = rhs.data_queue;
    }

    virtual ~UtlThreadSafePriorityQueue()
    {}

    // regular push
    inline void push(const T& rNewValue) {
        std::unique_lock<std::mutex> lk(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lk,[this]{return (data_queue.size() < capacity) || shutdownFlag;});
        if (!shutdownFlag) {
            data_queue.push(rNewValue);
        }
        data_cond.notify_one();
    }

    // move aware push
    inline void push(T&& newValue) {
        std::unique_lock<std::mutex> lk(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lk,[this]{return (data_queue.size() < capacity) || shutdownFlag;});
        data_queue.push(std::move(newValue));
        data_cond.notify_one();
    }

    // wait for non empty lambda condition before returning value
    inline void wait_and_pop(T& rValue) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        // ideally should return an invalid value
        if (!shutdownFlag) {
            rValue = data_queue.top();
            data_queue.pop();
        }
    }

    // wait for non empty lambda condition before returning shared pointer to value
    inline std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty() || shutdownFlag;});
        if (shutdownFlag) {
            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }
        return nullptr;
    }

    // return value in specified reference and flag indicating whether value
    // successfully returned or not
    inline bool try_pop(T& rValue) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()) {
            return false;
        }
        rValue = data_queue.front();
        data_queue.pop();
        return true;
    }

    // return shared pointer to value - which if set to nullptr,
    // indicates container was empty at the time of the call.
    inline std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    // thread safe method to check if the queue is empty
    // note that if it is empty
    inline bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }

    // shutdown support - wake up potentially sleeping queues
    inline void shutdown() {
        shutdownFlag = true;
        data_cond.notify_all();
    }
};


int main()
{    
//    auto comparator = []( const PriorityLevel& lhs, const PriorityLevel& rhs ) { 
//        return lhs < rhs; 
//    };
//    
//    std::priority_queue<PriorityLevel, std::vector<PriorityLevel>, 
//        decltype(comparator)> priorityQ(comparator);
    
    // the defults appear to be identical to the above decltype comparator
    // as it actually defaults to std::less<T> where T is PriorityLevel
    // and I implemented this as an operator overload
    std::priority_queue<PriorityLevel> priorityQ;
        
    std::vector<PriorityLevel>  testPriorites = {
        PriorityLevel(2, 'A', 1),
        PriorityLevel(1, 'A'),
        PriorityLevel(1, 'B', 1),
        PriorityLevel(2, 'A'),
        PriorityLevel(1, 'B', 3),
        PriorityLevel(2, 'A', 1),
        PriorityLevel(1, 'B', 2),
        PriorityLevel(2, 'A', 1),
        PriorityLevel(5, 'A'),
        PriorityLevel(5, 'A', 1),
        PriorityLevel(5, 'A', 2),
        PriorityLevel(5, 'A', 3),
        PriorityLevel(5, 'B'),
        PriorityLevel(5, 'B', 1)
    };

    UtlThreadSafePriorityQueue<PriorityLevel> priorityIPCQueue;    

    std::cout << "unordered priorities" << std::endl;
    std::cout << "====================" << std::endl;
    for (const auto& next : testPriorites) {
        std::cout << next << std::endl;
        priorityIPCQueue.push(next);
    }
    std::cout << std::endl;
    
    std::cout << "priority IPC queue" << std::endl;
    std::cout << "==================" << std::endl;
//    while (!priorityIPCQueue.empty()) {
//        PriorityLevel priorityLevel;
//        priorityIPCQueue.wait_and_pop(priorityLevel);
//        std::cout << priorityLevel << std::endl;
//    }
    
    // kick off 3 threads to work on the 
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 3; i++) {
        auto fut = std::async(std::launch::async, [](UtlThreadSafePriorityQueue<PriorityLevel>& rJobQueue) {
            while (!rJobQueue.empty()) {
                PriorityLevel priorityLevel;
                rJobQueue.wait_and_pop(priorityLevel);
                std::cout << "threadID[" << std::this_thread::get_id() << "]" << priorityLevel << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }, std::ref(priorityIPCQueue));
        futures.push_back(std::move(fut));
        // now taht the threads were launched asynchronously
        // let them do their work - sleep sufficiently here before collecting the results
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
    std::for_each(futures.begin(), futures.end(), [](std::future<void>& fut) {
        // this kicks off the threads
        std::cout << "here" << std::endl;
        fut.wait();
    });
}
