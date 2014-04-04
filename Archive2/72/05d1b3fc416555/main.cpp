#include <iostream>
#include <stdint.h>


template <typename T>
struct Ptr
{
    
    explicit Ptr(T* p)
    {
        data_ = reinterpret_cast<uintptr_t>(p);
        set(0);
    }
    
    uint16_t index() const { return data_ >> 48; }
    
    T* get() const
    {
        return reinterpret_cast<T*>(data_ & ((1ULL << 48) - 1));
    }
    
    void set(uint16_t v)
    {
        uintptr_t ip = reinterpret_cast<uintptr_t>(get());
        ip |= static_cast<uintptr_t>(v) << 48;
        data_ = ip;
    }
    
    uintptr_t data_;
};



int main()
{
    Ptr<int> p(new int(123));
    std::cout << (*p.get()) << ' ' << reinterpret_cast<uintptr_t>(p.get()) << ' '  << p.index() << std::endl;
    
    *p.get() = 456;
    p.set(789);
    std::cout << (*p.get()) << ' ' << reinterpret_cast<uintptr_t>(p.get()) << ' '  << p.index() << std::endl;
    
    
}