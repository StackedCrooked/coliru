#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <stddef.h>



/**
 * @brief The PacketBase class is the base class for the Packet class.
 *
 * Using this base class allows us to call the same constructor for each of the Packet constructors.
 * (Once the compiler supports C++11 delegating constructors this workaround won't be needed anymore.)
 */
struct PacketBase
{
    static const size_t cDefaultCapacity = 256;
    
    // minimum ethernet frame size is 60 bytes
    // ethernet header is 14 bytes
    // so we need 46 extra bytes at most
    static const size_t cMaxPadding = 46; 

    // Worst case cumulative header size in case of TCP is
    // TCP Header :  20
    // TCP Options:  40
    // IP  Header :  20
    // IP  Options:  40
    // VLAN       :   4
    // Ethernet   :  14
    // Total      : 138
    static const size_t cCumulativeHeaderSize = 138;

    PacketBase() :
        mBuffer(cDefaultCapacity),
        mBegin(mBuffer.size() - cMaxPadding),
        mEnd(mBegin)
    {
    }

    PacketBase(size_t inPayloadSize) :
        mBuffer(inPayloadSize + cCumulativeHeaderSize),
        mBegin(mBuffer.size() - cMaxPadding),
        mEnd(mBegin)
    {
        assert(inPayloadSize > cMaxPadding);
    }

    std::vector<uint8_t> mBuffer;
    std::vector<uint8_t>::size_type mBegin;
    std::vector<uint8_t>::size_type mEnd;
};



class Packet : public PacketBase
{
public:
    Packet() : PacketBase()
    {
    }

    template<typename T>
    explicit Packet(const T & inInitialData) : PacketBase(std::max(sizeof(T) + cMaxPadding, cDefaultCapacity))
    {
        push_front(inInitialData);
    }

    explicit Packet(const std::vector<uint8_t> & inData) : PacketBase(std::max(inData.size(), cDefaultCapacity))
    {
        push_front(inData);
    }


    template<typename FwdIt>
    explicit Packet(FwdIt begin, FwdIt end) : PacketBase(std::max<std::size_t>(end - begin, cDefaultCapacity))
    {
        push_front(&*begin, end - begin);
    }

    Packet(const uint8_t * inData, size_t inSize) : PacketBase(std::max(inSize, cDefaultCapacity))
    {
        push_front(inData, inSize);
    }

    // GCC 4.5 doesn't have the "=default" yet.
    Packet(Packet&& rhs) : PacketBase(std::move(rhs))
    {
    }

    Packet& operator=(Packet&& rhs)
    {
        PacketBase& base = *this;
        base = std::move(rhs);
        return *this;
    }

    void clear()
    {
        mBegin = mBuffer.size() - cMaxPadding;
        mEnd = mBegin;
    }

    //! Add padding bytes at the end of the packet.
    //! The maximum padding size is very limited (See cMaxPadding variable).
    void addPadding(size_t inSize)
    {
        assert(mEnd + inSize <= mBuffer.size());
        mEnd += inSize;
    }

    void push_front(const void * inData, size_t inSize)
    {
        if (inSize > mBegin)
        {
            unsigned extraSize = inSize - mBegin;
            std::vector<uint8_t> extraBuffer(extraSize);
            mBuffer.insert(mBuffer.begin(), extraBuffer.begin(), extraBuffer.end());
            mBegin += extraSize;
            mEnd += extraSize;
        }

        assert(mBegin >= inSize);
        mBegin -= inSize;
        assert(mBegin + inSize <= mBuffer.size());
        memcpy(&mBuffer[mBegin], inData, inSize);
    }

    void push_front(const std::vector<uint8_t> & inData)
    {
        push_front(inData.data(), inData.size());
    }

    template<typename T>
    void push_front(const T & inHeader)
    {
        push_front(reinterpret_cast<const uint8_t *>(&inHeader), sizeof(inHeader));
    }

    size_t getTotalSize() const
    {
        return mEnd - mBegin;
    }

    const uint8_t * data() const
    {
        return mBuffer.data() + mBegin;
    }

    size_t size() const
    {
        return getTotalSize();
    }

    void resize(std::size_t newSize)
    {
        if (newSize > size())
        {
            auto diff = newSize - size();
            mBuffer.resize(newSize + cMaxPadding);
            mEnd += diff;
            return;
        }
        else
        {
            auto diff = size() - newSize;
            mEnd -= diff;
        }
    }

    std::vector<uint8_t> getBuffer() const
    {
        return std::vector<uint8_t>(mBuffer.begin() + mBegin, mBuffer.begin() + mEnd);
    }

private:
    Packet(const Packet &); // disable copy
    Packet & operator=(const Packet &); // disable assigment
};


std::ostream & operator<<(std::ostream & os, const Packet & inPacket)
{
    return os << "Packet(" << inPacket.size() << ")";
}


int main()
{
    Packet packet;
    for (int i = 0; i != 10; ++i)
    {
        packet.push_front(i);
        std::cout << packet << std::endl;
    }
}