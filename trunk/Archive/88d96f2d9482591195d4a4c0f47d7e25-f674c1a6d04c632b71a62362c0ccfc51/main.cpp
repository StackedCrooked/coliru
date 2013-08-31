#include <array>
#include <atomic>
#include <future>
#include <iostream>
#include <vector>
#include <assert.h>
#include <stdint.h>
#include <string.h>


#define ASSERT(c) \
    std::cout  << __FILE__ << ":" << __LINE__ << ": " << #c \
    << ((c) ? " => OK!" : " => ***FAIL***") << std::endl; \
    assert(c);


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
        auto allowed = std::min(len, read_available());
        memcpy(buf, read_begin(), allowed);
        mNumRead += allowed;
        return allowed;
    }
    
    unsigned write(const void* buf, unsigned len)
    {
        auto allowed = std::min(len, write_available());
        memcpy(write_begin(), buf, allowed);
        mNumWritten += allowed;
        return allowed;
    }
    
    unsigned read_available() const
    {
        return mNumWritten - mNumRead;
    }
    
    unsigned write_available() const
    {
        return size() - read_available();
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
    
    const uint8_t* read_begin() const
    {
        return data() + (mNumRead % size());
    }
    
    uint8_t* write_begin()
    {
        return data() + (mNumRead % size());
    }
    
    std::vector<uint8_t> mData;
    std::atomic<unsigned> mNumRead;
    std::atomic<unsigned> mNumWritten;
};


void test()
{
    AtomicBuffer buf(8u);
    ASSERT(buf.read_available() == 0u);
    ASSERT(buf.write_available() == 8u);
    
    auto write_msg = "Hello World!";
    
    auto num_written = 0u;
    auto num_read = 0u;
    
    num_written += buf.write(&write_msg[0], sizeof(write_msg));
    ASSERT(buf.read_available() == num_written);
    
    
    char read_msg[sizeof(write_msg)];
    num_read = buf.read(read_msg, num_written - num_read);
    ASSERT(num_read == num_written);
    
    std::cout << buf.read_available() << std::endl;
    std::cout << buf.write_available() << std::endl;
    
}


void threaded_test()
{
    AtomicBuffer buf(128u);
    
    const std::string msg = "abcdefghijklmnopqrstuvwxyz0123456789";
    
    
    auto writer_future = std::async(std::launch::async, [&]{
        auto offset = 0u;
        while (offset != msg.size()) {
            offset += buf.write(
                msg.data() + offset,
                msg.size() - offset
            );
        }
    });
    
    
    auto reader_future = std::async(std::launch::async, [&]{
        std::string rcv;
        rcv.resize(256);
        auto num_read = 0u;
        
        while (num_read != rcv.size()) {
            num_read += buf.read(
                &rcv[0] + num_read,
                rcv.size() - num_read
            );
        }
        
        return rcv;
    }); 
}


int main()
{
    test();
}