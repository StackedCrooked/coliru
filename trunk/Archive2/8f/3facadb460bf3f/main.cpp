#include <string.h>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define SWAP(a,b) { (a)^=(b); (b)^=(a); (a)^=(b); }
#define SWAP16(x)\
{\
    uint8_t* ba = (uint8_t*)&(x);\
    if (mSwapNeeded && mPackNBO)\
        SWAP(ba[0], ba[1]);\
}
#define SWAP32(x)\
{\
    uint8_t* ba = (uint8_t*)&(x);\
    uint16_t* sa = (uint16_t*)&(x);\
\
    if (mSwapNeeded && mPackNBO)\
    {\
        SWAP(sa[0], sa[1]);\
        SWAP(ba[0], ba[1]);\
        SWAP(ba[2], ba[3]);\
    }\
}


class OldSafeBuffer {
public:
    intmax_t writeAt(const intmax_t& rIndex, const uint32_t val32);
    intmax_t writeAt(const intmax_t& rIndex, const int32_t val32);
    intmax_t readFrom(const intmax_t& rIndex, uint32_t& rVal32);
    intmax_t readFrom(const intmax_t& rIndex, int32_t& rVal32);
    intmax_t writeAt(const intmax_t& rIndex, const uint16_t val16);
    intmax_t writeAt(const intmax_t& rIndex, const int16_t val16);
    intmax_t readFrom(const intmax_t& rIndex, uint16_t& rVal16);
    intmax_t readFrom(const intmax_t& rIndex, int16_t& rVal16);
    intmax_t read(uint32_t& rVal32);
    intmax_t read(int32_t& rVal32);
    intmax_t read(uint16_t& rVal16);
    intmax_t read(int16_t& rVal16);
protected:
    // Actual memory storage.
    std::unique_ptr<char[]> mBuffer;
    // Buffer length
    intmax_t mBufferLength;
    // Represents the largest byte offset referenced.
    // Can be used to retrieve written length of buffer.
    intmax_t mHighWaterMark;
    // If set, caller wanted to pack data in network-byte-order.
    bool mPackNBO;
    // Set on construction, determines whether value needs to be byte-swapped.
    bool mSwapNeeded;
    // Used for file compatibility
    intmax_t mPosition;
};

/**
 * Small class to encapsulate some memory and assist in managing
 * its size. Allows flexible access.
 */
class UtlSafeBuffer
{
public:
    // define the byte order
    typedef enum ByteOrder {
        LittleEndian,
        BigEndian
    } ByteOrder;

    /**
     * default constructor for the smart buffer
     * 
     * @param rInitialSize
     *                  [in] initial size of the safe buffer -
     *                  default (256 bytes)
     * @param byteOrder [in] indicates Little or Big Endian format,
     *                  defaults to LittleEndian (network byte
     *                  order)
     */
    explicit UtlSafeBuffer(
        const intmax_t& rInitialSize,
        const ByteOrder byteOrder)
        : mBuffer(new char[rInitialSize])
        , mBufferLength(rInitialSize)
        , mHighWaterMark(-1)
        , mPackNBO((byteOrder == LittleEndian) ? false : true)
        , mSwapNeeded(false)
        , mPosition(0)
    {
        static uint8_t ba[] = {0xde, 0xad, 0xbe, 0xef};
        static uint32_t *i = (uint32_t *)ba;
        mSwapNeeded = (*i != 0xdeadbeef);
    }

    // copy constructor
    UtlSafeBuffer(const UtlSafeBuffer& rhs)
        : mBuffer(new char[rhs.mBufferLength])
        , mBufferLength(rhs.mBufferLength)
        , mHighWaterMark(rhs.mHighWaterMark)
        , mPackNBO(rhs.mPackNBO)
        , mSwapNeeded(rhs.mSwapNeeded)
        , mPosition(rhs.mPosition)
    {
        if (rhs.mBufferLength > 0) {
            memcpy(mBuffer.get(), rhs.mBuffer.get(), rhs.mBufferLength);
        }
    }

    // move constructor
    inline UtlSafeBuffer(UtlSafeBuffer&& rhs)
        : mBuffer(std::move(rhs.mBuffer))
        , mBufferLength(std::move(rhs.mBufferLength))
        , mHighWaterMark(std::move(rhs.mHighWaterMark))
        , mPackNBO(std::move(rhs.mPackNBO))
        , mSwapNeeded(std::move(rhs.mSwapNeeded))
        , mPosition(std::move(rhs.mPosition))
    {
        // prevent double frees
        rhs.mBufferLength = 0;
        rhs.mPosition = 0;
        rhs.mHighWaterMark = -1;
    }

    // non-throwing-swap idiom
    inline void swap(UtlSafeBuffer& rhs) throw () {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // no need to swap base members - as we are topmost class
        swap(mBuffer, rhs.mBuffer);
        swap(mBufferLength, rhs.mBufferLength);
        swap(mHighWaterMark, rhs.mHighWaterMark);
        swap(mPackNBO, rhs.mPackNBO);
        swap(mSwapNeeded, rhs.mSwapNeeded);
        swap(mPosition, rhs.mPosition);
    }

    // non-throwing copy-and-swap idiom unified assignment
    inline UtlSafeBuffer& operator=(UtlSafeBuffer rhs) {
        rhs.swap(*this);
        return *this;
    }

    // destructor
    inline virtual ~UtlSafeBuffer() 
    {};

    // clears out the buffer
    inline void clear(const intmax_t& rInitialSize = 256)
    {
        mBuffer.reset(new char[rInitialSize]);
        if (mBuffer) {
            memset(mBuffer.get(), 0, rInitialSize);
            mBufferLength = rInitialSize;
            mHighWaterMark = -1;
            mPosition = 0;
        } else {
            //throw std::exception("Out of Memory");
        }
    }

    /**
     * Checks to see if the memory buffer is large enough, re-allocates
     * memory contents if necessary.
     * 
     * @param rRequiredSize
     *               [in]required buffer size
     * @param bPreserveContents
     *               [in] flag to indicate whether we
     *               should preserve the existing
     *               contents of the buffer.
     * 
     * @return true if successful
     */
    inline bool ensureSize(
        const intmax_t& rRequiredSize,
        const bool bPreserveContents)
    {
        intmax_t nNewLength = 0;
        // check to see if we need to increase buffer capacity
        if (rRequiredSize > mBufferLength) {
            nNewLength = rRequiredSize * 2;
            std::unique_ptr<char[]> tempBuffer(new char[nNewLength]);
            if (tempBuffer) {
                if (mBuffer) {
                    // copy contents of old buffer to new one...
                    // if we already have contents in the buffer
                    if (bPreserveContents && (mHighWaterMark > 0)) {
                        memcpy(tempBuffer.get(), mBuffer.get(), mBufferLength);
                    } else { // recycling a buffer - ensure we reset position
                        mPosition = 0;
                    }
                }
                mBuffer = std::move(tempBuffer);
                mBufferLength = nNewLength;
            } else {
                //throw std::exception("Out of memory");
            }
        }
        return (mBuffer != nullptr);
    }

    template <typename T>
    inline intmax_t writeAt(const intmax_t& rIndex, const T val)
    {
        if (sizeof(T) > sizeof(int16_t)) {
            SWAP32(val);
        } else {
            SWAP16(val);
        }
        if (ensureSize((rIndex + sizeof(T)), true)) {
            memcpy(&mBuffer[rIndex], &val, sizeof(val));
            mHighWaterMark = std::max<intmax_t>(mHighWaterMark, (rIndex + (sizeof(T)-1)));
            mPosition = rIndex + sizeof(T);
            return sizeof(T);
        }
        return -1;
    }

    /**
     * Read value (signed or unsigned) from buffer at given byte offset.
     *
     * @param rIndex [in]
     * @param rVal   [out]
     *
     * @return BytesRead or -1 on error
     */
    template <typename T>
    inline intmax_t readFrom(const intmax_t& rIndex, T& rVal)
    {
        if ((rIndex + static_cast<intmax_t>(sizeof(T))) <= mBufferLength) {
            T* pVal = (T *)&mBuffer[rIndex];
            rVal = *pVal;
            // @JC Partial Template Specialization for 16 bit entities?
            if (sizeof(rVal) > sizeof(int16_t)) {
                SWAP32(rVal);
            } else {
                SWAP16(rVal);
            }
            mPosition = rIndex + sizeof(T);
            return sizeof(rVal);
        }
        return -1;
    }

    /**
     * read value from the current position in the buffer compatible 
     * with file reads
     *
     * @param rVal [out] value read from the buffer
     *
     * @return number of bytes read - should be sizeof (T)
     */
    template <typename T>
    inline intmax_t read(T& rVal)
    {
        if ((mPosition + static_cast<intmax_t>(sizeof(T))) <= mBufferLength) {
            T* pVal = (T *)&mBuffer[mPosition];
            rVal = *pVal;
            // @JC Partial Template Specialization for 16 bit entities?
            if (sizeof(rVal) > sizeof(int16_t)) {
                SWAP32(rVal);
            } else {
                SWAP16(rVal);
            }
            mPosition += sizeof(T);
            return sizeof(rVal);
        }
        return -1;
    }

    /**
     * Writes user specified buffer of size <code>rLength</code>
     * into this safe buffer starting at current position.<p>
     * The method also automatically resizes if required.
     * 
     * @param pBuffer [in] pointer to a user specified input buffer
     * @param rIndex  [in] offset within the buffer to write
     * @param rLength [in] length in bytes to write to this buffer
     * 
     * @return BytesWritten or -1 on error
     */
    inline intmax_t writeAt(
        const void* pBuffer, 
        const intmax_t& rIndex, 
        const intmax_t& rLength)
    {
        if (ensureSize(rIndex + rLength, true)) {
            memcpy(&mBuffer[rIndex], pBuffer, rLength);
            mHighWaterMark = std::max<intmax_t>(
                mHighWaterMark, (rIndex + rLength - 1));
            mPosition = rIndex + rLength;
            return rLength;
        }
        return -1;
    }

protected:
    // Actual memory storage.
    std::unique_ptr<char[]> mBuffer;

    // Buffer length
    intmax_t mBufferLength;

    // Represents the largest byte offset referenced.
    // Can be used to retrieve written length of buffer.
    intmax_t mHighWaterMark;

    // If set, caller wanted to pack data in network-byte-order.
    bool mPackNBO;

    // Set on construction, determines whether value needs to be byte-swapped.
    bool mSwapNeeded;

    // Used for file compatibility
    intmax_t mPosition;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::unique_ptr<char[]> temp(new char[1024]);
    UtlSafeBuffer safeBuffer(1024, UtlSafeBuffer::LittleEndian);
}
