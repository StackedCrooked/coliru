#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>


struct Pool
{
    static Pool& Get(std::size_t inRequestedSize)
    {
        static std::vector<std::unique_ptr<Pool>> fPools(100);
        std::size_t actual_size = nextpow2(inRequestedSize);
        std::size_t index = log2(inRequestedSize);
        
        std::cout << "Pool::Get " << " inRequestedSize=" << inRequestedSize << " actual_size=" << actual_size << " index=" << index << std::endl;
            
        if (fPools.size() <= inRequestedSize)
        {
            fPools.resize(inRequestedSize + 1);
        }

        auto& pool = fPools[index];
        if (!pool)
        {
            pool.reset(new Pool(actual_size));
        }
        return *pool;
    }
    
    Pool(std::size_t inSegmentSize) : mSegments(), mSegmentSize(inSegmentSize)
    {
        if (inSegmentSize < 10000)
        {
            mSegments.reserve(10);
        }
        else
        {
            mSegments.reserve(1);
        }
        
        while (mSegments.size() != mSegments.capacity())
        {
            mSegments.push_back(static_cast<std::uint8_t*>(malloc(inSegmentSize)));
        }
        std::cout << "mSegments.size=" << mSegments.size() << std::endl;
    }
    
    ~Pool()
    {
        while (!mSegments.empty())
        {
            std::free(mSegments.back());
            mSegments.pop_back();
        }
    }
    
    uint8_t* allocate()
    {
        if (mSegments.empty())
        {
            auto cap = mSegments.capacity();
            mSegments.reserve(2 * cap);
            for (std::size_t i = 0; i != cap; ++i)
            {
                mSegments.push_back(static_cast<std::uint8_t*>(malloc(mSegmentSize)));
            }
        }
        auto back = mSegments.back();
        mSegments.pop_back();
        return back;
    }
    
    void deallocate(uint8_t* data)
    {
        mSegments.push_back(data);
    }
    
    std::size_t getSegmentSize() const { return mSegmentSize; }
    
private:
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;
    
    static int nextpow2(int x)
    {
        if (x < 0)
        {
            return 0;
        }
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;
    }
    
    
    static int log2(int x)
    {
        int y;
        asm ("\tbsr %1, %0\n"
             : "=r"(y)
             : "r" (x)
        );
        return y;
    }
    
    std::vector<std::uint8_t*> mSegments;
    std::size_t mSegmentSize;
};



int main()
{
    for (int i = 1; i <= 100; ++i)
    {
        Pool::Get(i).allocate();
    }
    
    for (int i = 101; i < 2000000; i *= 1.2)
    {
        Pool::Get(i).allocate();
    }
}

