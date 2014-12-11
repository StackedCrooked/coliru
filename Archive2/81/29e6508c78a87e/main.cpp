#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <vector>


struct SegmentPool
{
    SegmentPool(std::size_t inSegmentSize) : mSegments(), mSegmentSize(inSegmentSize)
    {
    }

    SegmentPool(const SegmentPool&) = delete;
    SegmentPool& operator=(const SegmentPool&) = delete;

    ~SegmentPool()
    {
        while (!mSegments.empty())
        {
            std::free(mSegments.back());
            mSegments.pop_back();
        }
    }

    void* allocate()
    {
        if (mSegments.empty())
        {
            return malloc(mSegmentSize);
        }

        auto back = mSegments.back();
        mSegments.pop_back();
        return back;
    }

    void deallocate(void* data) { mSegments.push_back(data); }

    std::size_t getSegmentSize() const { return mSegmentSize; }

private:
    std::vector<void*> mSegments;
    std::size_t mSegmentSize;
};


struct MemoryPool
{
    MemoryPool() = default;
    MemoryPool(MemoryPool&&) noexcept = default;
    MemoryPool& operator=(MemoryPool&&) noexcept = default;
    ~MemoryPool() = default;

    void* allocate(std::size_t inRequestedSize)
    {
        return getPool(inRequestedSize).allocate();
    }

    void deallocate(void* data, std::size_t inRequestedSize)
    {
        return getPool(inRequestedSize).deallocate(data);
    }

private:
    static int nextpow2(int x)
    {
        if (x < 0) { return 0; }
        --x;
        x |= x >> 1;  x |= x >> 2;
        x |= x >> 4;  x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }

    static int log2(int x)
    {
        int y;
        asm ( "\tbsr %1, %0\n":"=r"(y): "r" (x));
        return y;
    }

    SegmentPool& getPool(std::size_t inRequestedSize)
    {
        auto it = mSegmentPools.find(inRequestedSize);
        if (it == mSegmentPools.end())
        {
            return *mSegmentPools.insert(SegmentPools::value_type(inRequestedSize, std::unique_ptr<SegmentPool>(new SegmentPool(nextpow2(inRequestedSize))))).first->second;
        }
        return *it->second;
    }

    typedef std::map<std::size_t, std::unique_ptr<SegmentPool>> SegmentPools;
    SegmentPools mSegmentPools;
};



template <typename T>
struct MemoryPoolAllocator
{
    typedef T * pointer;
    typedef const T * const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template<typename U>
    struct rebind
    { typedef MemoryPoolAllocator<U> other; };

    MemoryPoolAllocator(MemoryPool* inMemoryPool) : mMemoryPool(inMemoryPool) { }
    MemoryPoolAllocator(const MemoryPoolAllocator& rhs) : mMemoryPool(rhs.mMemoryPool) { }

    template <typename U>
    MemoryPoolAllocator(const MemoryPoolAllocator<U>& rhs) : mMemoryPool(rhs.mMemoryPool) { }
    
    MemoryPoolAllocator& operator=(const MemoryPoolAllocator& rhs)
    { mMemoryPool = rhs.mMemoryPool; return *this; }

    ~MemoryPoolAllocator() { }

    const T * address(const T& s) const { return &s; }
    T * address(T& r) const { return &r; }

    size_t max_size() const { return std::size_t(-1); }

    bool operator==(const MemoryPoolAllocator&) const { return true; }
    bool operator!=(const MemoryPoolAllocator& other) const { return !(*this == other); }

    void construct(T * const p, const T& t) const { new (static_cast<void *>(p)) T(t); }

    void destroy(T * const p) const { p->~T(); }

    T * allocate(size_t n) const { return n ? static_cast<T*>(mMemoryPool->allocate(n * sizeof(T))) : nullptr; }

    void deallocate(T * const p, const size_t n) const { mMemoryPool->deallocate(p, n * sizeof(T)); }

    template <typename U> 
    T * allocate(const size_t n, const U*) const { return this->allocate(n); }

private:
    MemoryPool* mMemoryPool;
};


#include <array>


struct Packet
{
    Packet(const char* b, const char* e) : Packet(std::allocator_arg, std::allocator<Packet>(), b, e) {}

    Packet(uint16_t inSize) : Packet(std::allocator_arg, std::allocator<Packet>(), inSize) {}

    template<typename Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, const char* b, const char* e)
    {
        using Other = typename Alloc::template rebind<char>::other;
        static_assert(sizeof(Impl<Other>) <= sizeof(mStorage), "");
        new (storage()) Impl<Other>(Other(alloc), b, e);
    }

    template<class Alloc>
    Packet(std::allocator_arg_t, Alloc alloc, uint16_t inSize)
    {
        using Other = typename Alloc::template rebind<char>::other;
        static_assert(sizeof(Impl<Other>) <= sizeof(mStorage), "");
        new (storage()) Impl<Other>(Other(alloc), inSize);
    }

    Packet(Packet&& rhs) { rhs.base().move_construct(storage()); }
    
    Packet(const Packet& rhs) { rhs.base().copy_construct(storage()); }
    
    Packet& operator=(Packet rhs) { swap(rhs); return *this; }
    
    ~Packet() { base().~Base(); }
    
    void push_back(const char* b, const char* e) { base().append(b, e); }

    void swap(Packet& rhs)
    {
        std::swap(mStorage[0], rhs.mStorage[0]);
        std::swap(mStorage[1], rhs.mStorage[1]);
        std::swap(mStorage[2], rhs.mStorage[2]);
    }

    const char* begin() const { return base().begin(); }
    char* begin() { return base().begin(); }

    const char* end() const { return base().end(); }
    char* end() { return base().end(); }

    const char* data() const { return begin(); }
    char* data() { return begin(); }

    std::size_t size() const { return base().size(); }

private:
    friend bool operator==(const Packet& lhs, const Packet& rhs)
    { return lhs.size() == rhs.size() && !memcmp(lhs.data(), rhs.data(), lhs.size()); }
    
    friend bool operator!=(const Packet& lhs, const Packet& rhs)
    { return !(lhs == rhs); }

    friend std::ostream& operator<<(std::ostream& os, const Packet& p)
    { for (char c : p) os << c; return os; }

    struct Base
    {
        Base(char* inData, uint16_t inSize) : mData(inData), mSize(inSize) { }

        Base(const Base&) = delete;
        Base& operator=(const Base&) = delete;

        virtual ~Base() { } 

        virtual void copy_construct(void* where) const = 0;
        virtual void move_construct(void* where) = 0;
        virtual void append(const char* b, const char* e) = 0;

        char* begin() { return mData; }
        char* end() { return begin() + size(); }

        const char* begin() const { return mData; }
        const char* end() const { return begin() + size(); }
        std::size_t size() const { return mSize; }
        
        const char* data() const { return begin(); }
        char* data() { return begin(); }

        char* mData;
        uint16_t mSize;
        uint16_t mExtra;
        uint32_t mExtra2;
    };

    template<class Alloc>
    struct Impl : Base, Alloc
    {
        using Alloc::allocate;
        using Alloc::deallocate;
        
        Impl(Alloc alloc, const char* b, const char* e) : Base(alloc.allocate(e - b), e - b), Alloc(alloc)
        { memcpy(mData, b, size()); }

        Impl(Alloc alloc, uint16_t inSize) : Base(alloc.allocate(inSize), inSize), Alloc(alloc) { }

        Impl(const Impl& rhs) : Base(nullptr, rhs.mSize), Alloc(rhs.getAlloc())
        { mData = allocate(mSize); memcpy(mData, rhs.mData, rhs.mSize); }

        Impl(Impl&& rhs) : Base(rhs.mData, rhs.mSize), Alloc(std::move(rhs.getAlloc()))
        { rhs.mData = nullptr; rhs.mSize = 0; }

        Impl& operator=(Impl rhs)
        { rhs.swap(*this); return *this; }

        ~Impl() { if (mData) deallocate(mData, size()); }

        const Alloc& getAlloc() const { return *this; }
        Alloc& getAlloc() { return *this; }

        virtual void copy_construct(void* where) const override final
        { new (where) Impl<Alloc>(*this); }

        virtual void move_construct(void* where) override final
        { new (where) Impl<Alloc>(std::move(*this)); }
        
        virtual void append(const char* b, const char* e) override final
        {
            Impl<Alloc> impl(getAlloc(), size() + e - b);
            memcpy(impl.data(), data(), size());
            memcpy(impl.data() + size(), b, e - b);
            swap(impl);
        }

        void swap(Impl& rhs)
        {
            std::swap(getAlloc(), rhs.getAlloc());
            std::swap(mData, rhs.mData);
            std::swap(mSize, rhs.mSize);
        }

        const char* begin() const { return mData; }
        std::size_t size() const { return mSize; }
    };

    const Base& base() const { return *static_cast<const Base*>(storage()); }
    Base& base() { return *static_cast<Base*>(storage()); }

    const void* storage() const { return mStorage.data(); }
    void* storage() { return mStorage.data(); }

    std::array<void*, 4> mStorage;
};


#include <algorithm>
#include <iostream>
#include <cassert>


int main()
{
    MemoryPool storage;
    MemoryPoolAllocator<char> alloc(&storage);

    for (int i = 0; i != 10; ++i)
    {
        std::string data = "*";
    
        Packet packet(std::allocator_arg, alloc, &*data.begin(), &*data.end());
        
        
        // duplicate
        packet.push_back(packet.begin(), packet.end());
        std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        
        // append one
        packet.push_back(&*data.begin(), &*data.end());
        std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        
        Packet packet2 = packet;
        assert(packet2 == packet);
        std::swap(packet, packet2);
        assert(packet2 == packet);
        
        // duplicate
        packet.push_back(packet.begin(), packet.end());
        std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        
        // append one
        packet.push_back(&*data.begin(), &*data.end());
        std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        
        Packet packet3(packet);
        assert(packet3 == packet);
        packet.push_back(&*data.begin(), &*data.end());
        
        // duplicate
        for (int i = 0; i != 4; ++i)
        {
            packet.push_back(packet.begin(), packet.end());
            std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        }
        
        // append one
        packet.push_back(&*data.begin(), &*data.end());
        std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        
        Packet packet4(packet);
        Packet packet5(std::move(packet));
        
        assert(packet4 == packet5);
        assert(packet.size() == 0);
        
        
        for (int i = 0; i != 200; ++i)
        {
            // append one
            packet.push_back(&*data.begin(), &*data.end());
            std::cout<< "packet.size=" << packet.size() << " data=" << packet << std::endl;
        }
    }
}



