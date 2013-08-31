#include <array>
#include <atomic>
#include <future>
#include <iostream>
#include <vector>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


std::atomic<bool> quit{false};


// One thread is only allowed to write.
// One thread is only allowed to read.
struct AtomicBuffer
{
    AtomicBuffer(std::size_t inSize) :
        mData(inSize),
        mNumRead(0),
        mNumWritten(0)
    {
    }
    
    unsigned read(void* buf, unsigned len)
    {
        unsigned num_written = mNumWritten;
        unsigned num_read = mNumRead;
        unsigned read_available = num_written - num_read;
        unsigned offset = num_written % mData.size();
        
        assert(num_written <= num_read);
        assert(num_written - num_read >= 0);
        assert(num_written - num_read < mData.size());
        auto data = &mData[0] + num_written;
        
        memcpy(buf, data, allowed);
        mNumRead = num_read + allowed;
        return allowed;
    }
    
    unsigned write(const void* buf, unsigned len)
    {
        unsigned num_written = mNumWritten;
        unsigned num_read = mNumRead;
        unsigned write_available = (mNumWritten == mNumRead) ? mData.size() : 0u;
        
        assert(num_written >= num_read);
        assert(num_written - num_read < mData.size());
        auto allowed = std::min(len, write_available);
        memcpy(&mData[0] + 
        mNumWritten = num_written + allowed;
        return allowed;
    }
    
    unsigned size() const
    {
        return mData.size();
    }
    
private:
    const uint8_t* data() const
    {
        return mData.data();
    }
    
    uint8_t* data()
    {
        return mData.data();
    }
    
    std::vector<uint8_t> mData;
    std::atomic<unsigned> mNumRead;
    std::atomic<unsigned> mNumWritten;
};


void threaded_test()
{
    AtomicBuffer shared_buffer(16u);    
    
    auto writer_future = std::async(std::launch::async, [&]{
        const std::string msg = "abcdefghijklmnopqrstuvwxyz0123456789";
        auto offset = 0u;
        while (!quit) {
            offset += shared_buffer.write(
                msg.data() + (offset % msg.size()),
                (msg.size() - (offset % msg.size())
            ));
        }
    });
    
    
    auto reader_future = std::async(std::launch::async, [&]{
        std::string receive;
        receive.resize(16);
        while (!quit) {
            auto num_read = shared_buffer.read(&receive[0], receive.size());
            if (num_read > 0) {
                receive.resize(num_read);
                std::cout << receive << std::flush;
            }
        }
    }); 
    
    writer_future.get();
    reader_future.get();
}


int main()
{
    // kill if deadlocked
    std::thread([]{ sleep(1); quit = true; }).detach();
    
    threaded_test();
}