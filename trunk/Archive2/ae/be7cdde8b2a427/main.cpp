#include <boost/ptr_container/ptr_vector.hpp>
#include <chrono>
#include <vector>
#include <thread>


using TimePoint = std::chrono::steady_clock::time_point;
using Nanoseconds = std::chrono::nanoseconds;


struct TransmitInterface
{
    virtual void write(const char*, std::size_t) = 0;
};


struct Flow
{
    int getNumPackets(TimePoint startTime, TimePoint currentTime, TimePoint& nextSendTime)
    {
        auto waitDuration = currentTime - (startTime + mNumSent * mInterval);
        nextSendTime = startTime + waitDuration;
        return ((currentTime - startTime) / mInterval) - mNumSent;
    }
    
    void transmit(TransmitInterface& out, TimePoint currentTime, int numAllowed)
    {
        for (int i = 0; i != numAllowed; ++i)
        {
            out.write(mPacket.data(), mPacket.size());
        }
        mTimeLastSent = currentTime;
        mNumSent += numAllowed;
    }
        
    std::vector<char> mPacket;
    Nanoseconds mInterval;
    std::uint64_t mNumSent;
    TimePoint mTimeLastSent;
    
};



struct Tx : TransmitInterface
{
    void run()
    {
        auto startTime = std::chrono::steady_clock::now();
        auto currentTime = startTime;
        
        for (;;)
        {
            TimePoint nextSendTime = TimePoint::max();
            for (Flow& flow : mFlows)
            {
                TimePoint localNextSendTime;
                
                auto numPackets = flow.getNumPackets(startTime, currentTime, localNextSendTime);
                
                if (localNextSendTime < nextSendTime)
                {
                    nextSendTime = localNextSendTime;
                }
                
                if (numPackets > 0)
                {
                    flow.transmit(*this, currentTime, numPackets);
                }
            }
            
            if (currentTime < nextSendTime)
            {
                std::this_thread::sleep_until(nextSendTime);
                currentTime = std::chrono::steady_clock::now();
            }
        }
    }
    
    void write(const char* data, std::size_t length)
    {
        mSocket.write(data, length);
    }
    
    using Flows = boost::ptr_vector<Flow>;
    
    struct Socket
    {
        void write(const char*, std::size_t);
    };
    
    Socket mSocket;
    Flows mFlows;
};
