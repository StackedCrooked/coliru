#include <atomic>
#include <cassert>
#include <future>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include "tbb/concurrent_queue.h"


using Buffer = std::vector<uint8_t>;
struct ReceivePacket : Buffer { using Buffer::Buffer; };
struct SendPacket : Buffer { using Buffer::Buffer; };
struct Segment : Buffer { using Buffer::Buffer; };

struct Stack
{    
    Stack() :
        mDispatcherThread([=]{ this->dispatcher_thread(); }),
        mRx(),
        mTx(),
        mQuit()
    {
    }
    
    ~Stack()
    {
        mQuit = true;
        mReceivePackets.push(ReceivePacket());
        mDispatcherThread.join();
    }
    
    void pop(ReceivePacket& received)
    {
        mRx++;
        SendPacket send_packet(received.begin(), received.end());
        push(send_packet);
    }
    
    void write(Segment& segment)
    {
        mSegments.push(segment);
    }
    
    uint64_t rx() const
    {
        return mRx;
    }
    
    uint64_t tx() const
    {
        return mTx;
    }
    
private:    
    void push(SendPacket& send)
    {
        mReceivePackets.push(ReceivePacket(send.begin(), send.end()));
        mTx++;        
    }
    
    void dispatcher_thread()
    {
        ReceivePacket receive;
        Segment segment;
        
        while (!mQuit)
        {
            if (mReceivePackets.try_pop(receive))
            {
                this->pop(receive);
            }
                        
            if (mSegments.try_pop(segment))
            {
                SendPacket send_packet(segment.begin(), segment.end());;
                this->push(send_packet);
            }
        }
        
        std::cout << "Quit flag is set. mSegments.size=" << mSegments.size()
                  << ". mReceivePackets.size=" << mReceivePackets.size()
                  << ". Rx=" << rx()
                  << ". Tx=" << tx()
                  << std::endl;
    }
    
    tbb::concurrent_bounded_queue<Segment> mSegments;
    tbb::concurrent_bounded_queue<ReceivePacket> mReceivePackets;
    std::thread mDispatcherThread;
    std::atomic<uint64_t> mRx;
    std::atomic<uint64_t> mTx;
    std::atomic<bool> mQuit;
};


int main()
{
    Stack stack;
    Segment segment(1500);
    ReceivePacket receive(1500);
    for (int i = 0; i != 1000; ++i)
    {
        stack.write(segment);
        
    }
    
    sleep(2);
}