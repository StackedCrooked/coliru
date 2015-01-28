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


// Thread-safe for single-producer and single-consumer.
struct CircularBuffer
{
    CircularBuffer(std::size_t inSize) :
        mBuffer(inSize),
        mNumRead(0),
        mNumWritten(0)
    {
    }

    std::size_t capacity() const
    {
        return mBuffer.capacity();
    }

    bool empty() const
    {
        return mBuffer.empty();
    }

    std::size_t read(uint8_t* buf, std::size_t len)
    {
        // first make a copy of the number of written bytes.
        std::size_t numWritten = mNumWritten;

        assert(numWritten >= mNumRead);

        // number of bytes available for reading is equal to the total number of
        // written bytes subtracted with the number of read bytes
        // with the input length as an upper bound
        auto available = numWritten - mNumRead;
        if (available > len)
        {
            available = len;
        }

        if (available == 0)
        {
            return 0;
        }

        for (auto i = 0UL; i != available; ++i)
        {
            // NOTE: we could increment mNumRead here to achieve
            //       more concurrency and less waiting.
            *buf++ = mBuffer.at((mNumRead + i) % capacity());
        }

        // this enables writer thread to start writing again
        mNumRead += available;
        return available;
    }

    std::size_t write(uint8_t* buf, std::size_t len)
    {
        std::size_t numRead = mNumRead;

        assert(mNumWritten >= numRead);

        // the number of bytes available for writing is equal to the the size
        // of the buffer plus the  of bytes written in the past mins the number
        // of read bytes in the  past
        auto availableSpace = capacity() - (mNumWritten - numRead);
        if (availableSpace > len)
        {
            availableSpace = len;
        }
        if (availableSpace == 0)
        {
            return 0;
        }

        for (unsigned i = 0; i != availableSpace; ++i)
        {
            // NOTE: maybe we can increment mNumWritten here to achieve
            //       a higher degree of concurrency
            mBuffer.push_back(*buf++);
        }

        mNumWritten += availableSpace;
        return availableSpace;
    }


    boost::circular_buffer<uint8_t> mBuffer;
    std::atomic<std::size_t> mNumRead;
    std::atomic<std::size_t> mNumWritten;
};


int main()
{
    // Our buffer has 10 bytes capacity;
    CircularBuffer buf(10);

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
            print(MakeString() << " last_read=" << n << " total_read=" << numWritten);
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