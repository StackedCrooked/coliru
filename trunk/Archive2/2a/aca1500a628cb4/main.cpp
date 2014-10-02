#include <random>
#include <atomic>
#include <queue>
#include <mutex>
#include <iostream>
#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <iterator>
#include <memory>
#include <vector>
#include <future>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <condition_variable>
#include <boost/optional.hpp>

using namespace std::chrono;

/**
 *  represents the szPriorityLevel<p>
 *
 * the szPriority Field contains a channel, priority character
 * [A-Z] (from highest priority to -lowest priority)
 * and an optional sequence number.
 */
class PriorityLevel {
public:
    // default constructor
    PriorityLevel(
        const int32_t& rChannel = -1,
        const char priorityChar = 'Z',
        const std::string& rFilename = std::string(),
        const boost::optional<int32_t>& rSequenceNum =
            boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar)
        , mFilename(rFilename)
        , mSequenceNum(rSequenceNum)
    {}

    // copy constructor
    PriorityLevel(const PriorityLevel& rhs)
        : mChannel(rhs.mChannel)
        , mPriorityChar(rhs.mPriorityChar)
        , mFilename(rhs.mFilename)
        , mSequenceNum(rhs.mSequenceNum)
    {}

    // move constructor
    PriorityLevel(PriorityLevel&& rhs)
        : mChannel(std::move(rhs.mChannel))
        , mPriorityChar(std::move(rhs.mPriorityChar))
        , mFilename(std::move(rhs.mFilename))
        , mSequenceNum(std::move(rhs.mSequenceNum))
    {
        // reset optionals - not really necessary
        rhs.mSequenceNum = boost::none;
    }

    // non-throwing-swap idiom
    inline void swap(PriorityLevel& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // no need to swap base members - as we are topmost class
        swap(mChannel, rhs.mChannel);
        swap(mPriorityChar, rhs.mPriorityChar);
        swap(mFilename, rhs.mFilename);
        swap(mSequenceNum, rhs.mSequenceNum);
    }

    // non-throwing copy-and-swap idiom unified assignment
    PriorityLevel& operator=(PriorityLevel rhs) {
        rhs.swap(*this);
        return *this;
    }

    // equality operator
    inline bool operator==(const PriorityLevel& rhs) const {
        return std::tie(mChannel, mPriorityChar, mFilename, mSequenceNum) ==
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhs.mSequenceNum);
    }

    // inequality operator opposite to equality operator
    inline bool operator!=(const PriorityLevel& rhs) const {
        return !(operator==(rhs));
    }

    /**
     * comparator that orders the elements in the
     * priority_queue<p>
     *
     * Implemented via a lexicographical comparison using
     * std::tuple<T...> as a helper. Tuple comparison works as
     * follows: compares the first elements, if they are equivalent,
     * compares the second elements, if those are equivalent,
     * compares the third elements, and so on. All comparison
     * operators are short - circuited; they do not access tuple
     * elements beyond what is necessary to determine the result of
     * the comparison. note that the presence of the sequence number
     * assigns a lower priority (bigger value 1) contribution to the
     * lexicographical nature of the comparison
     *
     * @param rhs    [in] PriorityLevel to compare against
     *
     * @return 'true' if this has lower priority than rhs
     */
    inline bool operator<(const PriorityLevel& rhs) const {
        auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
        auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
        return std::tie(mChannel, mPriorityChar, mFilename, seqNum) >
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhsSeqNum);
    }

    // operator>=() is opposite to operator<()
    inline bool operator>=(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    // operator>() implemented so that it now works with std::sort()
    // preserving the strict weak ordering mathematical rules
    inline bool operator>(const PriorityLevel& rhs) const {
        auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
        auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
        return std::tie(mChannel, mPriorityChar, mFilename, seqNum) <
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhsSeqNum);
    }

    // operator<=() is opposite to operator>()
    inline bool operator<=(const PriorityLevel& rhs) const {
        return !(operator>(rhs));
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] PriorityLevel to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    inline friend std::ostream& operator << (
        std::ostream& os, const PriorityLevel& rhs) {
        os << rhs.getPriorityStr();
        return os;
    }

    // channel getter
    inline int32_t getChannel() const {
        return mChannel;
    }

    // priority char getter
    inline char getPriorityChar() const {
        return mPriorityChar;
    }

    // filename getter
    inline std::string getFilename() const {
        return mFilename;
    }

    // string representation of the priority string
    inline std::string getPriorityStr(const bool bShowFilename = false) const {
        std::stringstream ss;
        ss << mChannel << mPriorityChar;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        if (bShowFilename) {
            // print the filename to the right
            ss << "[" << mFilename << "]";
        }
        return ss.str();
    }
private:
    // channel number - top level order field
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // '_dr/_xr' filename+ext associated with this priority thread
    std::string mFilename;
public:
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};

/**
 * Branch representing fundamental building block of
 * a priority tree containing szPriority entries.<p>
 *
 * Each priority tree struct contains a vector of concurrent
 * priorities that can be scheduled to run in the thread pool -
 * note that the thread pool must have no entries associated
 * with the current channel running before enqueueing these
 * tasks. The application must wait for the thread pool to
 * complete these tasks before queuing up the dependent tasks
 * described in the mNextNode smart pointer. If mNextNode is
 * unassigned (nullptr), then we have reached the end of the
 * tree.
 */
struct PriorityNode {
    explicit PriorityNode(
        const std::vector<PriorityLevel>& rConcurrent,
        const std::shared_ptr<PriorityNode>& rNext = std::shared_ptr<PriorityNode>(),
        const size_t& rDepth = 0)
        : mConcurrent(rConcurrent)
        , mNextNode(rNext)
        , mDepth(rDepth)
        , mDone(false)
    {}

    /**
    * Stream insert operator<p>
    *
    * @param os     [in,out] output stream
    * @param rhs    [in] PriorityLevel to send to the output
    *               stream.
    *
    * @return a reference to the updated stream
    */
    inline friend std::ostream& operator << (
        std::ostream& os, const PriorityNode& rhs) {
        // indent 2 spaces per depth level
        std::string indent = rhs.mDepth > 0 ?
            (std::string("|") +
            std::string((rhs.mDepth * 2) - 1, '_')) :
            std::string();
        // print out the concurrent threads that 
        // can be scheduled with the thread pool
        for (const auto& next : rhs.mConcurrent) {
            os << indent << next << std::endl;
        }
        // print the dependent priorities that can only
        // be scheduled when the concurrent ones are finished
        if (rhs.mNextNode) {
            os << *rhs.mNextNode << std::endl;
        }
        return os;
    }
    // these are all equivalent thread priorities
    // that can be run simultaneously
    std::vector<PriorityLevel> mConcurrent;

    // these are concurrent threads that must be AFTER all 
    // mConcurrent tasks have completed (exiting the thread pool)
    std::shared_ptr<PriorityNode> mNextNode;

    // recursion depth
    size_t mDepth;

    // flag indicating finished enqueueing all this node's mConcurrent tasks
    bool mDone;
};

class TestCBClass {
public:
    // default constructor
    TestCBClass(const int& rValue = 1)
        : mValue(rValue) {
        std::cout << "~TestCBClass()" << std::endl;
    }
    
    // dtor
    virtual ~TestCBClass() {
        std::cout << "~TestCBClass()" << std::endl;
    }
    
    // task entry point
    static std::string testStaticMethod(
        const PriorityLevel& rPrty, 
        const size_t& rSleepTimeSecs) {
        // note the start time
        auto startTime = system_clock::to_time_t(system_clock::now());
        std::stringstream ss;
        std::this_thread::sleep_for(seconds(rSleepTimeSecs));
        std::lock_guard<std::mutex> lock(gMutexGuard);
        // log the runtime statistics
        ss << "tid[" << std::this_thread::get_id() 
            << "], prty[" << rPrty.getPriorityStr(true) 
            << "], start[" << std::ctime(&startTime) 
            << "] duration " << rSleepTimeSecs << "(s)";
        return ss.str();
    }
private:
    int mValue;
    static std::mutex gMutexGuard;
};

std::mutex TestCBClass::gMutexGuard;

using task_t = std::function<void(void)>;

// FORWARD DECLARATIONS
template <typename Priority>
class prioritized_task {
private:
    Priority priority;
    task_t task;
public:
    explicit prioritized_task(const Priority& rPriority, task_t&& f)
        : priority(rPriority)
        , task(std::forward<task_t>(f))
    {}

    // used for priority ordering tasks
    inline bool operator < (const prioritized_task& rhs) const {
        return this->priority < rhs.priority;
    }

    // functor operator used to invoke priority_task
    inline void operator()() {
        task();
    }
    // priority getter
    inline Priority getPriority() const {
        return priority;
    }
};



template <typename Priority>
class UtlThreadPool {
private:
    std::vector<std::thread> mWorkers;
    std::priority_queue<prioritized_task<Priority>> mTasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> isActive;
public:
    UtlThreadPool(const size_t& rNumThreads = std::thread::hardware_concurrency())
        : isActive(true)
    {
        for (size_t i = 0; i < rNumThreads; i++) {
            mWorkers.emplace_back(std::thread(
                &UtlThreadPool::scheduler_loop, this));
        }
    }

    // copy constructor - do not allow
    UtlThreadPool(const UtlThreadPool&) = delete;

    // assignment - do not allow
    UtlThreadPool& operator=(const UtlThreadPool&) = delete;

    template<class F, class P, class... Args>
    auto enqueue(P priority, F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        typedef typename std::result_of<F(Args...)>::type return_type;
        // Don't allow enqueueing after stopping the pool
        if (!isActive.load()) {
            throw std::runtime_error(
                "enqueue on stopped UtlThreadPool");
        }

        // @JC changed return_type() to return_type(Args...)
        auto task = std::make_shared<std::packaged_task<return_type(Args...)>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mTasks.push(prioritized_task<Priority>(priority, 
                [task](void) { (*task)(); }));
        }
        condition.notify_one();
        return result;
    }

    // check the remaining size of the pool
    size_t pending(void) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        return this->mTasks.size();
    }

    // close the thread pool - this will wait for all queued up jobs to finish
    // additional jobs will not allowed to get posted to the queue for scheduling
    void close() {
        if (isActive.load()){
            // only stop the threads if transitioning 
            // from active to inactive
            isActive.store(false);
            condition.notify_all();
            for (std::thread& t : mWorkers) {
                t.join();
            }
        }
    }

    // destructor - waits for thread pool to finish active jobs
    virtual ~UtlThreadPool(void){
        close();
    }
private:
    // this 
    inline void scheduler_loop() {
        std::unique_ptr<Priority> pCurrentPrty;
        for (;;) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // wait for some task to get queued or for the atomic 
            // isActive flag to become inactive
            condition.wait(lock, [this, &pCurrentPrty] {
                if (!mTasks.empty() && 
                    pCurrentPrty && pCurrentPrty->getPriorityStr() != 
                    mTasks.top().getPriority().getPriorityStr() && 
                    pCurrentPrty->getPriorityStr().length() != 
                    mTasks.top().getPriority().getPriorityStr().length()) {
                    std::cout << "priority change" << std::endl;
                }
                return (!mTasks.empty() || !isActive.load());
            });
            // only exit when no more tasks on the queue
            if (!isActive.load() && mTasks.empty()) {
                return;
            }
            // update the top priority job that is currently running
            pCurrentPrty = std::make_unique<Priority>(mTasks.top().getPriority());
            // move next task off the priority queue
            auto nextTask(std::move(mTasks.top()));
            pCurrentPrty = std::make_unique<Priority>(nextTask.getPriority());
            // queue housekeeping
            mTasks.pop();
            // release the lock allowing new entries to be queued
            lock.unlock();
            // execute the task forwarding stored arguments with the call
            // this is the magic that works inside a thread pool
            // _Ret operator()(_Types... _Args) const 
            nextTask();
        }
    }
};

int main()
{    
    // more realistic priorities - Dassault
    std::vector<PriorityLevel> gPriorities = {
        PriorityLevel(1, 'A', "[foo._dr]"),
        PriorityLevel(3, 'A', "[bar._dr]"),
        PriorityLevel(1, 'B', "[foo._dr]", 1),
        PriorityLevel(1, 'B', "[bar._dr]", 1),
        PriorityLevel(1, 'B', "[foo._dr]", 2),
        PriorityLevel(1, 'B', "[bar._dr]", 2),
        PriorityLevel(1, 'B', "[foo._dr]", 3),
        PriorityLevel(1, 'B', "[foo._dr]", 3),
        PriorityLevel(1, 'B', "[foo._dr]", 4),
        PriorityLevel(1, 'B', "[foo._dr]", 5),
        PriorityLevel(1, 'C', "[foo._dr]", 1), // test
        PriorityLevel(1, 'C', "[foo._dr]", 2), // test
        PriorityLevel(1, 'A', "[foo._dr]", 1), // test
        PriorityLevel(2, 'A', "[foo._dr]"),
        PriorityLevel(2, 'B', "[foo._dr]", 1),
        PriorityLevel(2, 'B', "[foo._dr]", 2),
        PriorityLevel(2, 'B', "[foo._dr]", 3),
        PriorityLevel(2, 'B', "[foo._dr]", 2)
    };

    // channel only comparator - don't care about the order of the other fields
    const auto channelPred = [](const PriorityLevel& a, const PriorityLevel& b) {
        return a.getChannel() < b.getChannel();
    };

    // ignore the filename in the priority ordering - maybe add back later
    // as the last field to compare - not sure yet.
    const auto priorityPred = [](const PriorityLevel& a, const PriorityLevel& b) {
        // sequence number presence is important, its value is of secondary importance
        // which is why it is compared as the last entry in the tuple
        const auto seqNumA = a.mSequenceNum ? /*a.mSequenceNum.get()*/1 : 0;
        const auto seqNumB = b.mSequenceNum ? /*b.mSequenceNum.get()*/1 : 0;
        const auto channelA = a.getChannel();
        const auto channelB = b.getChannel();
        const auto priorityCharA = a.getPriorityChar();
        const auto priorityCharB = b.getPriorityChar();
        // no real need to include channel as all channels compared
        // using this comparator will have matching channels already
        // left in for completeness.
        return std::tie(channelA, priorityCharA, seqNumA) <
            std::tie(channelB, priorityCharB, seqNumB);
    };

    // order the PriorityLevels in descending order 
    // (highest to lowest priority). Note that higher priority
    // values use lower priority characters and sequence numbers
    // which is why the PriorityLevel operator> uses < comparisons
    // in the tuple fields
    std::sort(gPriorities.begin(), gPriorities.end(),
        std::greater<PriorityLevel>());
#if 0          
    std::cout << "priorities - ordered by channel" << std::endl;
    std::copy(gPriorities.begin(), gPriorities.end(),
        std::ostream_iterator<PriorityLevel>(
            std::cout, "\n"));
    std::cout << std::endl;
#endif

    std::map<int32_t, std::shared_ptr<PriorityNode>> priorityInfo;
    // iterate over each of the channel ranges
    for (auto iter = gPriorities.begin(); iter != gPriorities.end();) {
        auto channelRange = std::equal_range(iter, gPriorities.end(), 
            iter->getChannel(), channelPred);
#if 0
        std::cout << "channel [" << iter->mChannel << "] priorities - unordered" << std::endl;
        std::copy(channelRange.first, channelRange.second,
            std::ostream_iterator<PriorityLevel>(
                std::cout, "\n"));
        std::cout << std::endl;
#endif
        // convert the channelRange into a sorted list of priorities
        std::vector<PriorityLevel> ch_ptys(channelRange.first, channelRange.second);
        std::sort(ch_ptys.begin(), ch_ptys.end(), priorityPred);
        // print the channel ordered priorities
#if 0
        std::cout << "channel [" << iter->mChannel << "] priorities - ordered" << std::endl;
        std::copy(ch_ptys.begin(), ch_ptys.end(),
            std::ostream_iterator<PriorityLevel>(
                std::cout, "\n"));
        std::cout << std::endl;
#endif
        // iterate over sub ranges within the channel ordered priorities 
        auto prevRange = std::make_pair(ch_ptys.begin(), ch_ptys.begin());
        std::shared_ptr<PriorityNode> currentNode, rootNode;
        size_t depth = 0;
        for (auto iter1 = ch_ptys.begin(); iter1 != ch_ptys.end();) {
            auto range = std::equal_range(
                iter1, ch_ptys.end(), *iter1, priorityPred);
            // this represents all the equivalent priority levels
            auto concurrent = std::vector<PriorityLevel>(range.first, range.second);
#if 0
            std::cout << "identical priorities" << std::endl;
            std::copy(range.first, range.second,
                std::ostream_iterator<PriorityLevel>(
                    std::cout, "\n"));
            std::cout << std::endl;
#endif
            // build a priority tree here
            if (!currentNode) {
                currentNode = std::make_shared<PriorityNode>(
                    concurrent, std::shared_ptr<PriorityNode>(), depth++);
                if (!rootNode) {
                    rootNode = currentNode;
                }
            } else {
                currentNode->mNextNode = std::make_shared<PriorityNode>(
                    concurrent, std::shared_ptr<PriorityNode>(), depth++);
                currentNode = currentNode->mNextNode;
            }
            prevRange = range;
            iter1 = range.second;
        }

        priorityInfo[iter->getChannel()] = rootNode;
        std::cout << *rootNode;
        iter = channelRange.second;
    }
    
    time_point<system_clock> start, now;
    start = system_clock::now();

    typedef std::result_of<decltype(&TestCBClass::testStaticMethod)(
        PriorityLevel, size_t)>::type ThreadResult;
    std::map<int32_t, std::vector<ThreadResult>> resultInfo;
    // thread pool's destructor will set the stop
    // flag & wait to join all active threads in the pool
    UtlThreadPool<PriorityLevel> priorityThreadPool(5);
    {
        std::default_random_engine generator;
        // generate sleep intervals in the range 3-10 seconds with normal distribution
        std::uniform_int_distribution<int> distribution(7, 12);
        auto timeMaker = std::bind(distribution, generator);
        // declare asynchronous and back to back (serial) futures of thread results
        std::map<int32_t, std::vector<std::future<ThreadResult>>> asyncs, serials;
        bool bAllTasksQueued = false;
        while (!bAllTasksQueued) {
            // enqueue as many threads from the top of the PriorityNode as possible
            // adding any Nodes with follow up tasks to serial futures that have 
            // to be completed.
            for (auto& next : priorityInfo) {
                auto& channel = next.first;
                auto& pNode = next.second;
                // check for pending serial futures on this channel
                if (serials.find(channel) == serials.cend()) {
                    // check to see if the futures need to be placed 
                    // in serials or asyncs
                    if (pNode->mNextNode) {
                        // reserve space in serials
                        serials[channel] = std::vector<
                            std::future<ThreadResult>>();
                        // enqueue concurrent tasks -> serialFutures 
                        for (auto priorityLevel : pNode->mConcurrent) {
                            auto sleepSecs = timeMaker();
                            std::cout << "serialQ [" << priorityLevel
                                << "] duration " << sleepSecs << "(s)" << std::endl;
                            auto future = priorityThreadPool.enqueue(priorityLevel,
                                std::bind(&TestCBClass::testStaticMethod, 
                                    priorityLevel, sleepSecs));
                            serials[channel].emplace_back(std::move(future));
                        }
                        // flag the node as finished - we have enqueued all its 
                        // mConcurrent tasks with the thread pool
                        pNode->mDone = true;
                        // navigate deeper into the priority tree - this will 
                        // be used next time round the loop
                        next.second = pNode->mNextNode;
                    } else { // finished serial dependencies for this channel
                        if (!pNode->mDone) {
                            // reserve move space in asyncs
                            if (asyncs.find(channel) == asyncs.cend()) {
                                asyncs[channel] = std::vector<
                                    std::future<ThreadResult>>();
                            }
                            // enqueue concurrent tasks -> asyncs 
                            for (auto priorityLevel : pNode->mConcurrent) {
                                auto sleepSecs = timeMaker();
                                std::cout << "asynchQ [" << priorityLevel
                                    << "] duration " << sleepSecs << "(s)" << std::endl;
                                auto future = priorityThreadPool.enqueue(priorityLevel,
                                    std::bind(&TestCBClass::testStaticMethod, 
                                        priorityLevel, sleepSecs));
                                asyncs[channel].emplace_back(std::move(future));
                            }
                            // flag the node as finished - we have enqueued all its 
                            // mConcurrent tasks with the thread pool
                            pNode->mDone = true;
                        }
                    }
                }
                // terminating loop condition
                bAllTasksQueued = serials.empty();
            }

            // check for existing back to back channel thread relationships
            if (!serials.empty()) {
                // scan each channel checking for completed future groups.  
                // each channel's groups of priority threads is similar 
                // to a boost::thread_group @JC check if boost is better... 
                auto iter = serials.begin();
                while (iter != serials.end()) {
                    auto& channel = iter->first;
                    auto& futures = iter->second;
                    // check to see if the current channel's future's 
                    // have their shared state ready.  When they are, we can 
                    // move them to the async queue for result collection later
                    if (std::find_if(futures.cbegin(), futures.cend(),
                        [&](const std::future<ThreadResult>& nextFut) {
                            return nextFut.wait_for(seconds::zero()) != 
                                std::future_status::ready; }) == futures.cend()) {
                        // found completed serial future group, so move it
                        // to the async futures, allocating space if necessary
                        if (asyncs.find(channel) == asyncs.cend()) {
                            asyncs[channel] = std::vector<std::future <ThreadResult>>();
                        }
                        std::cout << "moving [" << futures.size()
                            << "] thread(s) to asynchQ for ch["
                            << channel << "]" << std::endl;

                        //now = system_clock::now();
                        //duration<double> elapsed_seconds = now - start;
                        //std::cout << "total time elapsed: " << elapsed_seconds.count() << "s\n";

                        std::move(futures.begin(), futures.end(),
                            std::back_inserter(asyncs[channel]));
                        // this will invalidate channel and futures above - but that is OK
                        // since we are done with them and we have moved the futures anyway
                        iter = serials.erase(iter);
                        // loop around enqueueing the next non 
                        // available thread priorities
                        break;
                    }
                }
            }
            std::this_thread::sleep_for(milliseconds(100));
        }

        // at this stage we must have no serials
        // associated with any of the channels
        for (auto& next : asyncs) {
            std::vector<ThreadResult> results;
            for (auto& nextFut : next.second) {
                auto result = nextFut.get();
                results.emplace_back(std::move(result));
            }
            resultInfo[next.first] = std::move(results);
        }
        for (auto& next : resultInfo) {
            std::cout << "results for ch[" << next.first << "]" << std::endl;
            for (auto& nextRes : next.second) {
                std::cout << nextRes << std::endl;
            }
        }

        now = system_clock::now();
        duration<double> elapsed_seconds = now - start;
        std::cout << "total time elapsed: " << elapsed_seconds.count() << "s\n";
        // wait for threads to complete
        priorityThreadPool.close();
    }
}