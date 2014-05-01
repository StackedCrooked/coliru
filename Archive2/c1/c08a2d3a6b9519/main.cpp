#include <boost/circular_buffer.hpp>
#include <atomic>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
#include <stdint.h>


std::vector<uint8_t> generateTestData(unsigned n);
void print(std::string str);
inline std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec);


struct MakeString
{
    template <typename T>
    MakeString & operator<<(const T & datum);
    MakeString & operator<<(uint8_t n);
    operator std::string() const;
    std::string str() const;
    std::ostringstream mBuffer;
};


template<unsigned Capacity>
struct ConcurrentBuffer
{
    ConcurrentBuffer() :
        mNumWritten(0),
        mPadding(),
        mNumRead(0),
        mBuffer()
    {
        (void)mPadding;
    }

    std::size_t capacity() const
    {
        return Capacity;
    }

    bool empty() const
    {
        return mNumRead == mNumWritten;
    }

    std::size_t read(uint8_t* buf, std::size_t len)
    {
        assert(mNumWritten >= mNumRead);
        std::size_t numWritten = mNumWritten;
        std::size_t numRead = mNumRead;

        // number of bytes available for reading is equal to the total number of
        // written bytes subtracted with the number of read bytes
        // with the input length as an upper bound
        auto count = std::min(numWritten - numRead, len);

        if (count == 0)
        {
            return 0;
        }

        for (auto i = 0UL; i != count; ++i)
        {
            *buf++ = mBuffer[(numRead + i) % Capacity];
        }
        
        mNumRead = numRead + count;

        return count;
    }

    std::size_t write(uint8_t* buf, std::size_t len)
    {
        assert(mNumWritten >= mNumRead);
        
        std::size_t numRead = mNumRead;
        std::size_t numWritten = mNumWritten;


        // the number of bytes available for writing is equal to the the size
        // of the buffer plus the  of bytes written in the past mins the number
        // of read bytes in the  past
        auto count = std::min(Capacity + numWritten - numRead, len);
        if (count == 0)
        {
            return 0;
        }
        for (unsigned i = 0; i != count; ++i)
        {
            mBuffer[(numWritten + i) % Capacity] = *buf++;
        }
        mNumWritten += count;
        return count;
    }
    
private:
    std::atomic<std::size_t> mNumWritten;
    char mPadding[64];
    std::atomic<std::size_t> mNumRead;
    std::array<uint8_t, Capacity> mBuffer;
};


int main()
{
    ConcurrentBuffer<10> buf;

    // The writer will write this to the buffer until all data has been sent.
    // The reader will read from this buffer until all test data has been received.
    auto testData = generateTestData(1000);


    //
    // Reader thread
    //
    std::thread([&] {
        std::vector<uint8_t> readBuffer(testData.size());
        auto numReceived = 0UL;
        while (numReceived != testData.size()) {
            if (auto n = buf.read(&readBuffer[0] + numReceived, readBuffer.size() - numReceived)) {
                numReceived += n;
                print(MakeString() << " +" << n);
            }
        }
        assert(testData == readBuffer);
    }).detach();


    //
    // Write thread (main thread)
    // 
    auto numWritten = 0UL;
    while (numWritten != testData.size()) {
        if (auto n = buf.write(testData.data() + numWritten, testData.size() - numWritten)) {
            numWritten += n;
            print(MakeString() << " -" << n);
            if (numWritten == testData.size()) {
                print("WRITER buffer is complete.");
                break;
            }
        }
    }
}



std::vector<uint8_t> generateTestData(unsigned n)
{
    std::vector<uint8_t> data;
    data.reserve(n);
    while (data.size() != data.capacity())
    {
        data.push_back(data.size());
    }
    return data;
}


void print(std::string str)
{
    static std::mutex fMutex;
    std::lock_guard<std::mutex> lock(fMutex);
    std::cout << str << '\n';
}


inline std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec)
{
    for (auto& el : vec)
    {
        os << std::setw(2) << std::setfill('0') << static_cast<int>(el) << ' ';
    }
    return os;
}



template <typename T>
MakeString& MakeString::operator<<(const T & datum)
{
    mBuffer << datum;
    return *this;
}


MakeString& MakeString::operator<<(uint8_t n)
{
    mBuffer << std::setw(2) << std::setfill('0') << static_cast<int>(n) << ' ';
    return *this;
}


MakeString::operator std::string() const
{ return mBuffer.str(); }


std::string MakeString::str() const
{ return mBuffer.str(); }