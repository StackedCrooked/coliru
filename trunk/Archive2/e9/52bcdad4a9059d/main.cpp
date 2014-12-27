#ifndef STACK_PACKET_H
#define STACK_PACKET_H


#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <chrono>


namespace Stack {
    
    
using Nanoseconds = std::chrono::nanoseconds;


class Packet
{
public:
    Packet() : Packet(std::allocator_arg, std::allocator<std::uint8_t>{})
    {
    }

    // This is the *innermost* constructor.
    // Other constructors delegate to this one.
    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc) :
        mImpl(CreateImpl(alloc)),
        mRefCount(CreateRefCount(alloc))
    {
    }

    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, const std::uint8_t* b, const std::uint8_t* e) :
        Packet(std::allocator_arg, alloc)
    {
        push_front(b, e);
    }

    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, const std::uint8_t* b, const std::uint8_t* e, const Nanoseconds& inTimestamp) :
        Packet(std::allocator_arg, alloc)
    {
        push_front(b, e);
        setTimestamp(inTimestamp);
    }

    Packet(const std::uint8_t* b, const std::uint8_t* e) :
        Packet(std::allocator_arg, std::allocator<std::uint8_t>{}, b, e)
    {
    }

    Packet(const std::uint8_t* b, const std::uint8_t* e, const Nanoseconds& inTimestamp) :
        Packet(std::allocator_arg, std::allocator<std::uint8_t>{}, b, e, inTimestamp)
    {
        setTimestamp(inTimestamp);
    }

    Packet(const char* b, const char* e) :
        Packet(std::allocator_arg, std::allocator<std::uint8_t>{}, b, e)
    {
    }

    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, const char* b, const char* e) :
        Packet(std::allocator_arg, alloc)
    {
        push_front(b, e);
    }

    Packet(const char* b, const char* e, const Nanoseconds& inTimestamp) :
        Packet(std::allocator_arg, std::allocator<std::uint8_t>{}, b, e, inTimestamp)
    {
        setTimestamp(inTimestamp);
    }

    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, const char* b, const char* e, const Nanoseconds& inTimestamp) :
        Packet(std::allocator_arg, alloc)
    {
        push_front(b, e);
        setTimestamp(inTimestamp);
    }

    Packet(Packet&& rhs) :
        mImpl(rhs.mImpl),
        mRefCount(rhs.mRefCount)
    {
        rhs.mImpl = nullptr;
        rhs.mRefCount = nullptr;
    }

    Packet& operator=(Packet&& rhs)
    {
        Packet(std::move(rhs)).swap(*this);
        return *this;
    }

    Packet(const Packet& rhs) :
        mImpl(rhs.mImpl),
        mRefCount(rhs.mRefCount)
    {
        if (mImpl && mRefCount)
        {
            ++(*mRefCount);
        }
    }

    Packet& operator=(const Packet& rhs)
    {
        Packet(rhs).swap(*this);
        return *this;
    }

    ~Packet()
    {
        if (mImpl && mRefCount && 0 == --(*mRefCount))
        {
            mImpl->destroy(mRefCount);
        }
    }

    Nanoseconds getTimestamp() const
    {
        if (!mImpl) return {};
        return mImpl->mTimestamp;
    }

    void setTimestamp(Nanoseconds inTimestamp)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->mTimestamp = inTimestamp;
    }

    void clear()
    {
        if (!mImpl) return;
        mImpl->clear();
    }

    void swap(Packet& rhs) noexcept
    {
        std::swap(mImpl, rhs.mImpl);
        std::swap(mRefCount, rhs.mRefCount);
    }

    void push_front(const std::uint8_t* data, std::size_t length)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->push_front(data, length);
    }

    void push_front(const std::uint8_t* b, const std::uint8_t* e)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->push_front(b, e - b);
    }

    void push_front(const char* data, std::size_t length)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->push_front(reinterpret_cast<const std::uint8_t*>(data), length);
    }

    void push_front(const char* b, const char* e)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->push_front(reinterpret_cast<const std::uint8_t*>(b), e - b);
    }

    void push_front(const void* inData, std::size_t inSize)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->push_front(static_cast<const std::uint8_t*>(inData), inSize);
    }

    void push_front(const std::string& data)
    {
        if (!mImpl) mImpl = CreateImpl();
        push_front(data.data(), data.data() + data.size());
    }

    template<typename T>
    typename std::enable_if<std::is_pod<T>::value, void>::type
    push_front(const T& t)
    {
        if (!mImpl) mImpl = CreateImpl();
        push_front(reinterpret_cast<const char*>(&t), sizeof(t));
    }

    std::size_t size() const
    {
        if (!mImpl) return 0;
        return mImpl->size();
    }

    bool empty() const
    {
        return !size();
    }

    std::size_t capacity() const
    {
        if (!mImpl) return 0;
        return mImpl->capacity();
    }

    void reserve(std::size_t new_capacity)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->reserve(new_capacity);
    }

    void resize(std::size_t length)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->resize(length);
    }

    std::size_t use_count() const
    {
        if (!mImpl) return 0;
        return *mRefCount;
    }

    bool unique() const
    {
        return use_count() <= 1;
    }

    void addPadding(std::size_t inPadding)
    {
        if (!mImpl) mImpl = CreateImpl();
        mImpl->addPadding(inPadding);
    }

    const std::uint8_t* data() const { return mImpl->data(); }
    const std::uint8_t* begin() const { return mImpl->begin(); }
    const std::uint8_t* end() const { return mImpl->end(); }

    std::uint8_t* data() { return mImpl->data(); }
    std::uint8_t* begin() { return mImpl->begin(); }
    std::uint8_t* end() { return mImpl->end(); }

private:
    using RefCount = uint8_t;

    // Ethernet requires frame size of at least 60 bytes.
    // Ethernet header is 14 bytes, which is the smallest possible frame size.
    // So we foresee 46 (60 - 14) extra bytes at the right side of the data.
    enum { cMaxPadding = 46 }; 

    // Polymorphic base allows us to type-erase the allocator in the derived class.
    struct Base
    {
        Base() {}

        virtual ~Base() {}

        virtual void destroy(RefCount*& outRefCount) = 0;

        void push_front(const std::uint8_t *data, std::size_t len)
        {
            auto current_size = size();
            auto required_capacity = current_size + len;
            reserve(required_capacity);

            mBegin -= len;
            std::memcpy(begin(), data, len);
        }

        void reserve(std::size_t length)
        {
            if (length > capacity())
            {
                grow(length - capacity());
            }
        }

        void resize(std::size_t new_size)
        {
            if (new_size < size())
            {
                mBegin += size() - new_size;
            }
            else if (new_size > size())
            {
                auto difference = new_size - size();
                reserve(new_size);
                mBegin -= difference;
                memset(begin(), 0, difference);
            }
            else // length == size()
            {
                // no action required
            }
            
            assert(size() == new_size);
        }

        void clear()
        {
            mBegin = mCapacity;
            mEnd = mBegin;
        }

        void addPadding(std::size_t inSize)
        {
            std::memset(end(), 0, inSize);
            mEnd += inSize;
        }

        virtual void grow(std::size_t length) = 0;

        const std::uint8_t* data() const { return mData + mBegin; }
        std::uint8_t* data() { return mData + mBegin; }

        const std::uint8_t* begin() const { return mData + mBegin; }
        const std::uint8_t* end() const { return mData + mEnd; }

        std::uint8_t* begin() { return mData + mBegin; }
        std::uint8_t* end() { return mData + mEnd; }

        std::size_t size() const { return mEnd - mBegin; }
        std::size_t capacity() const { return mCapacity; }

        std::uint8_t* mData = nullptr;
        std::uint16_t mBegin = 0;
        std::uint16_t mEnd = 0; // can go beyond capacity in case of padding
        std::uint16_t mCapacity = 0;
        Nanoseconds mTimestamp {0};
    };

    template<typename Alloc>
    struct Impl : Base, private Alloc // using inheritance to enable empty-base optimization
    {
        Impl(Alloc alloc) : Base(), Alloc(alloc)
        {
        }

        Impl(const Impl&) = delete;
        Impl& operator=(const Impl&) = delete;

        void destroy(RefCount*& outRefCount) override final
        {
            auto alloc_copy = static_cast<Alloc&>(*this);
            if (mData)
            {
                alloc_copy.deallocate(mData, capacity() + cMaxPadding);
                mData = nullptr;
            }
            this->~Impl();
            alloc_copy.deallocate(reinterpret_cast<std::uint8_t*>(this), sizeof(Impl<Alloc>));
            alloc_copy.deallocate(reinterpret_cast<std::uint8_t*>(outRefCount), sizeof(RefCount));
            outRefCount = nullptr;
        }

        virtual void grow(std::size_t grow_size) override final
        {
            auto old_capacity = mCapacity;
    		auto new_capacity = old_capacity + grow_size;

            auto& alloc = static_cast<Alloc&>(*this);
            auto memory = alloc.allocate(new_capacity + cMaxPadding);
            if (mData)
            {
                std::memcpy(memory + mBegin + grow_size, mData + mBegin, size());
                alloc.deallocate(mData, capacity() + cMaxPadding);
            }
            mBegin += grow_size;
            mData = memory;
            mEnd += grow_size;
            mCapacity += grow_size;
        }
    };

    template<typename Alloc>
    static Base* CreateImpl(Alloc alloc)
    {
        using Other = typename Alloc::template rebind<std::uint8_t>::other;
        Other other{alloc};
        return new (other.allocate(sizeof(Impl<Other>))) Impl<Other>(other);
    }

    template<typename Alloc>
    static RefCount* CreateRefCount(Alloc alloc)
    {
        using Other = typename Alloc::template rebind<std::uint8_t>::other;
        Other other{alloc};
        return new (other.allocate(sizeof(RefCount))) RefCount(1);
    }

    static Base* CreateImpl()
    {
        return CreateImpl(std::allocator<char>());
    }

    static RefCount* CreateRefCount()
    {
        return CreateRefCount(std::allocator<char>());
    }

    Base* mImpl;
    RefCount* mRefCount;
};


} // namespace Stack


#endif // STACK_PACKET_H


#include <iostream>


int main()
{
    Stack::Packet packet;
    packet.push_front("123");
    packet.push_front("abc");
    std::cout << std::string(packet.begin(), packet.end()) << std::endl;
}


