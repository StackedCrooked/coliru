#include <cstddef>
#include <cstdint>
#include <chrono>
#include <iostream>



namespace Detail {
namespace {

using yes = std::uint8_t;
using no = std::uint16_t;

template<typename T> auto is_buffer(T&&, int) -> decltype(std::declval<T>().data(), std::declval<T>().size(), yes());
template<typename T> auto is_buffer(T&&, long) -> decltype(no());
} }



namespace Utils { 
/**
 * PacketAdaptor wraps a packet of any type and provides
 * a common interface to the data, size and timestamp.
 *
 * Method mappings can be created by injecting adl-enabled overloads
 * inside the namespace where the input packet is defined.
 * 
 * Usage example:
 *
 *   // TransmitPacket.h contains original packet definition
 *   namespace Tx {
 *      struct TransmitPacket { ... };
 *   }
 *
 *   // User header or cpp file where the mapping is defined
 *   namespace Tx { // re-open the Tx namespace
 *     std::uint16_t adl_get_packet_size(const TransmitPacket& p) { p.GetTransmitSize(); };
 *     const std::uint8_t* adl_get_packet_data(const TransmitPacket& p) { p.GetTransmitData(); }
 *     std::chrono::nanoseconds adl_get_packet_timestamp(const TransmitPacket& p) { return std::chrono::nanoseconds(10 * p.GetNapatechTimeStamp()); }
 *
 *   }
 *
 */
struct PacketAdaptor
{
    // Defaulted constructor is needed to preserve pod-ness.
    PacketAdaptor() = default;

    // Constructor which accepts any type of packet for which the adl overloads work.
    template<typename PacketType>
    /*implicit*/ PacketAdaptor(const PacketType& t) :
        mData(adl_get_packet_data(t), adl_get_packet_size(t)),
        mTimestamp(adl_get_packet_timestamp(t))
    {
    }

    const std::uint8_t* data() const
    {
        return mData.getPtr();
    }

    std::uint16_t size() const
    {
        return mData.getTag();
    }

    std::chrono::nanoseconds timestamp() const
    {
        return mTimestamp;
    }

private:
    // Linux only uses 48-bit of the 64-bit pointer objects.
    // TaggedPtr enables using the remaining 16-bit as extra storage.
    // Here we use it to store the packet size.
    template<typename T>
    struct TaggedPtr
    {
        // defaulted constructor is required to preserve POD-ness of the PacketAdaptor class.
        TaggedPtr() = default;

        explicit TaggedPtr(const T* p, std::uint16_t tag) : mStorage(reinterpret_cast<std::uintptr_t>(p))
        {
            setTag(tag);
        }

        std::uint16_t getTag() const { return mStorage >> 48; }

        void setTag(std::uint16_t v)
        {
            std::uintptr_t ip = reinterpret_cast<std::uintptr_t>(getPtr());
            ip |= static_cast<std::uintptr_t>(v) << 48;
            mStorage = ip;
        }

        T* getPtr() const
        {
            return reinterpret_cast<T*>(mStorage & ((1ULL << 48) - 1));
        }

        void setPTr(T* t)
        {
            mStorage = TaggedPtr(t, getTag()).mStorage;
        }

        std::uintptr_t mStorage;
    };

    TaggedPtr<std::uint8_t> mData;
    std::chrono::nanoseconds mTimestamp;
};


static_assert(std::is_pod<PacketAdaptor>::value, "");
    
}


namespace Tx
{
    struct TransmitPacket
    {
        std::size_t GetSendSize() const { return __LINE__; }
        const std::uint8_t* GetSendData() const { return (const std::uint8_t*)__LINE__; }
        std::uint64_t GetSendTimeStamp() const { return __LINE__; }
    };
}

namespace Rx
{
    struct ReceivePacket
    {
        std::size_t GetReceiveSize() const { return __LINE__; }
        const std::uint8_t* GetReceiveData() const { return (const std::uint8_t*)__LINE__; }
        std::uint64_t GetReceiveTimeStamp() const { return __LINE__; }
    };
}


namespace Rx
{
    std::size_t adl_get_packet_size(const ReceivePacket& p)
    {
        return p.GetReceiveSize();
    }

    const std::uint8_t* adl_get_packet_data(const ReceivePacket& p)
    {
        return p.GetReceiveData();
    }

    std::chrono::nanoseconds adl_get_packet_timestamp(const ReceivePacket& p)
    {
        return std::chrono::nanoseconds(p.GetReceiveTimeStamp());
    }
}


// Injection outside of the original file
namespace Tx
{
    std::size_t adl_get_packet_size(const TransmitPacket& p)
    {
        return p.GetSendSize();
    }

    const std::uint8_t* adl_get_packet_data(const TransmitPacket& p)
    {
        return p.GetSendData();
    }

    std::chrono::nanoseconds adl_get_packet_timestamp(const TransmitPacket& p)
    {
        return std::chrono::nanoseconds(p.GetSendTimeStamp());
    }
}


#define assert_true(cond) do { std::cout << __FILE__ << ":" << __LINE__ << ": " << #cond << " " << std::flush << ((cond) ? "=> PASS" : "=> FAIL") << std::endl; } while (0);


int main()
{
    Tx::TransmitPacket tx;
    Rx::ReceivePacket rx;

    Utils::PacketAdaptor adapt_tx(tx);
    assert_true(adapt_tx.size() == tx.GetSendSize());
    assert_true(adapt_tx.data() == tx.GetSendData());
    assert_true(adapt_tx.timestamp() == std::chrono::nanoseconds(tx.GetSendTimeStamp()));

    Utils::PacketAdaptor adapt_rx(rx);
    assert_true(adapt_rx.size() == rx.GetReceiveSize());
    assert_true(adapt_rx.data() == rx.GetReceiveData());
    assert_true(adapt_rx.timestamp() == std::chrono::nanoseconds(rx.GetReceiveTimeStamp()));
}


