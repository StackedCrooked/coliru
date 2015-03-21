#include "tbb/concurrent_queue.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <sstream>
#include <thread>


//#include <glog/logging.h>

struct LogItem
{
    ~LogItem()
    {
        static std::mutex m;
        std::lock_guard<std::mutex> l(m);
        std::cout << ss.str() << std::endl;
    }
    
    std::stringstream ss;
};



#define LOG(INFO) LogItem().ss



using Frame = std::string;
using Counter = std::uint64_t;
using AtomicCounter = std::atomic<std::uint64_t>;
using TimePoint = std::chrono::steady_clock::time_point;
using Nanoseconds = std::chrono::nanoseconds;


struct TransmitInterface
{
    virtual void write(const Frame& inFrame) = 0;
};


struct Flow
{
    int getNumberOfAvailablePackets(TimePoint startTime, TimePoint currentTime, TimePoint& nextSendTime)
    {
        auto waitDuration = currentTime - (startTime + mNumSent * mInterval);
        nextSendTime = startTime + waitDuration;
        return ((currentTime - startTime) / mInterval) - mNumSent;
    }

    void transmit(TransmitInterface& out, TimePoint currentTime, int numAllowed)
    {
        for (int i = 0; i != numAllowed; ++i)
        {
            out.write(mBlastFrame);
        }
        mTimeLastSent = currentTime;
        mNumSent += numAllowed;
    }

    Frame mBlastFrame;
    Nanoseconds mInterval;
    std::uint64_t mNumSent;
    TimePoint mTimeLastSent;

};





struct Loopback
{
    void send(const Frame& inFrame)
    {
        if (getCurrentLoad() + inFrame.size() > mCapacity)
        {
            mDropped += inFrame.size();
            LOG(INFO) << "Loopback.dropped=" << mDropped << " Load=" << getCurrentLoad() << "/" << mCapacity;
            return;
        }

        mQueue.push(inFrame);
        mWritten += inFrame.size();
        LOG(INFO) << "Loopback.written=" << mWritten << " Load=" << getCurrentLoad() << "/" << mCapacity;
    }

    Frame receive()
    {
        Frame result;
        mQueue.pop(result);
        mRead += result.size();
        LOG(INFO) << "Loopback.read=" << mRead << " Load=" << getCurrentLoad() << "/" << mCapacity;
        return result;
    }

    Counter getCurrentLoad() const
    {
        return mWritten - mRead;
    }

    Counter mCapacity = 300;
    AtomicCounter mRead{0};
    AtomicCounter mWritten{0};
    AtomicCounter mDropped{0};
    tbb::concurrent_bounded_queue<Frame> mQueue;
};



struct Thread
{
    template<typename F>
    Thread(F f) : mThread(f) {}

    ~Thread() { mFlag = true; mThread.join(); }

    explicit operator bool() const { return mFlag; }

    std::atomic<bool> mFlag{false};
    std::thread mThread;
};


Loopback gSocket;

struct Rx
{
    Rx() : mThread([this] { run(); }) {}

    ~Rx()
    {
        gSocket.send(Frame());
    }

    void run()
    {
        for (;;)
        {
            auto frame = gSocket.receive();
            if (frame.empty())
            {
                LOG(INFO) << "Rx got empty frame. Quitting!";
                return;
            }

            auto send_time = *reinterpret_cast<const std::chrono::steady_clock::time_point*>(frame.data());
            auto latency = std::chrono::microseconds(10);

            std::this_thread::sleep_until(send_time + latency);
        }
    }

    AtomicCounter mReceived{0};
    Thread mThread;
};


struct Tx : TransmitInterface
{
    Tx() : mThread([this] { run(); })
    {
    }

    void run()
    {
        auto startTime = std::chrono::steady_clock::now();
        auto currentTime = startTime;

        for (;;)
        {
            if (!mThread) return;
            auto nextSendTime = TimePoint::max();
            for (Flow& flow : mFlows)
            {
                TimePoint localNextSendTime;

                auto numPackets = flow.getNumberOfAvailablePackets(startTime, currentTime, localNextSendTime);

                if (localNextSendTime < nextSendTime)
                {
                    nextSendTime = localNextSendTime;
                }

                if (numPackets > 0)
                {
                    flow.transmit(*this, currentTime, numPackets);
                }
            }

            if (nextSendTime == TimePoint::max())
            {
                continue;
            }

            if (currentTime < nextSendTime)
            {
                if (!mThread) return;
                std::this_thread::sleep_until(nextSendTime);
                currentTime = std::chrono::steady_clock::now();
            }
        }
    }

    void write(const Frame& inFrame)
    {
        gSocket.send(inFrame);
    }

    using Flows = boost::ptr_vector<Flow>;



    Flows mFlows;
    Thread mThread;
};


Rx rx;
Tx tx;


void run_test()
{
    for (int i = 1; i <= 1000; ++i)
    {
        auto now = std::chrono::steady_clock::now();
        auto b = reinterpret_cast<const char*>(&now);
        tx.write(Frame(b, b + sizeof(now)) + Frame(i % 100, '\0'));

    }
}


int main(int, char** /*argv*/)
{
    for (int i = 0; i != 1; ++i)
    {
        run_test();
    }
    LOG(INFO) << "End of program.";
}
