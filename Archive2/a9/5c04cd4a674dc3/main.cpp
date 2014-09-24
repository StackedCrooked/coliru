#include <iostream>
#include <stdint.h>


template <typename T>
struct Ptr
{
    
    explicit Ptr(T* p) : data_(reinterpret_cast<uintptr_t>(p))
    {
    }
    
    uint16_t get_metadata() const { return data_ >> 48; }
    
    void set_metadata(uint16_t v)
    {
        uintptr_t ip = reinterpret_cast<uintptr_t>(get());
        ip |= static_cast<uintptr_t>(v) << 48;
        data_ = ip;
    }
    
    T* get() const
    {
        return reinterpret_cast<T*>(data_ & ((1ULL << 48) - 1));
    }
    
    T* operator->() { return get(); }
    const T* operator->() const { return get(); }
    
    friend bool operator==(Ptr lhs, Ptr rhs)
    {
        return lhs.get() == rhs.get();
    }
    
    uintptr_t data_;
};



int main()
{
    Ptr<int> p(new int(123));
    Ptr<int> q{p};
    std::cout << "metadata: " << p.get_metadata() << std::endl;
    std::cout << "p==q? " << (p == q) << std::endl;
    
    p.set_metadata(123);
    std::cout << "metadata: " << p.get_metadata() << std::endl;
    
    std::cout << "p==q? " << (p == q) << std::endl;
    std::cout << "p==q? " << (p == q) << std::endl;
}

