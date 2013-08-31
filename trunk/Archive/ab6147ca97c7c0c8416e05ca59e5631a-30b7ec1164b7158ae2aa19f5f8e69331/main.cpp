#include <functional>
#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <assert.h>
#include <unistd.h>
#include "tbb/concurrent_queue.h"


struct Element
{
    Element() : mNext(), mRx(), mQueue(), mThread(std::bind(&Element::consume, this)) {}
    
    Element(Element& inNext) :
        mNext(&inNext),
        mRx(),
        mQueue(),
        mThread(std::bind(&Element::consume, this))
    {
    }
    
    Element(Element&&) = default;
    Element& operator=(Element&&) = default;
    
    ~Element()
    {
        mQueue.push(0);
        mThread.join();
    }
    
    void push(uint64_t n)
    {
        mQueue.push(n);
    }
    
private:
    void consume()
    {
        for (;;)
        {
            uint64_t n;
            mQueue.pop(n);
            if (!n) return;
            mRx++;
            if (mNext)
            {
                mNext->push(n);
            }
        }
    }
    
    Element* mNext;
    uint64_t mRx;
    tbb::concurrent_bounded_queue<uint64_t> mQueue;
    std::thread mThread;
};


struct ChainBase
{
    ChainBase(std::size_t inSize) : mQuit(false)
    {
        mElements.reserve(inSize);
        mElements.resize(1);
        while (mElements.size() != inSize)
        {
            Element& back = mElements.back();
            mElements.push_back(std::move(Element(back)));
        }
    }
        
    
    std::atomic<bool> mQuit;
    std::vector<Element> mElements;
};


struct Chain : protected ChainBase
{
    Chain(std::size_t inSize) : ChainBase(inSize), mThread(std::bind(&Chain::produce, this))
    {
    }
    
    ~Chain()
    {
        quit();
    }
    
    void quit()
    {
        if (!mQuit)
        {
            mQuit = true;
            mElements.clear();
            mThread.join();
        }
    }
        
    
private:
    void produce()
    {
        if (mElements.empty())
        {
            return;
        }
        
        auto& front = mElements.front();
        while (!mQuit)
        {
            front.push(1);
        }
        front.push(0);
    }
    
    
    std::thread mThread;
};


int main()
{
    Chain chain(10);
    sleep(2);
    chain.quit();
}
