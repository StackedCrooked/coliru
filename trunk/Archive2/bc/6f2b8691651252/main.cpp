#include <vector>
#include <cstdlib>
#include <iostream>

void* alloc_regular(std::size_t sz) { std::cout << "R"; return std::malloc(sz); }
void* alloc_simd16(std::size_t sz)  { std::cout << "S"; return std::malloc(sz); }
void* alloc_simd32(std::size_t sz)  { std::cout << "Q"; return std::malloc(sz); }

void dealloc_regular(void* ptr, std::size_t sz) { std::cout << "r"; std::free(ptr); }
void dealloc_simd16(void* ptr, std::size_t sz)  { std::cout << "s"; std::free(ptr); }
void dealloc_simd32(void* ptr, std::size_t sz)  { std::cout << "q"; std::free(ptr); }

// stateful allocator, needs c++11 stdlib and compiler

enum class MyAllocatorType {
    REGULAR,
    SIMD16,
    SIMD32,
    /* etc */
};

template<class T>
class MyAllocator {
public:

    using value_type = T;

    MyAllocator() : type_{MyAllocatorType::REGULAR} {}
    MyAllocator(MyAllocatorType t) : type_{t} {}
    MyAllocator(const MyAllocator& other) : type_{other.type_} {}
    MyAllocator& operator=(const MyAllocator& other) { type_ = other.type_; }
    bool operator==(const MyAllocator& other) { return type_ == other.type_; }
    bool operator!=(const MyAllocator& other) { return type_ != other.type_; }

    T* allocate(std::size_t sz)
    {
        switch (type_) {
        case MyAllocatorType::REGULAR:
            return reinterpret_cast<T*>(alloc_regular(sizeof(T)*sz));
        case MyAllocatorType::SIMD16:
            return reinterpret_cast<T*>(alloc_simd16(sizeof(T)*sz));
        case MyAllocatorType::SIMD32:
            return reinterpret_cast<T*>(alloc_simd32(sizeof(T)*sz));
        }
        return nullptr;
    }

    void deallocate(T* ptr, std::size_t sz)
    {
        switch (type_) {
        case MyAllocatorType::REGULAR:
            dealloc_regular(ptr, sizeof(T)*sz);
            break;
        case MyAllocatorType::SIMD16:
            dealloc_simd16(ptr, sizeof(T)*sz);
            break;
        case MyAllocatorType::SIMD32:
            dealloc_simd32(ptr, sizeof(T)*sz);
            break;
        }
    }

private:
    MyAllocatorType type_;
};

template<class T>
using MyVector = std::vector<T, MyAllocator<T>>;

int main()
{
    MyAllocator<int> a1{MyAllocatorType::REGULAR};
    MyAllocator<int> a2{MyAllocatorType::SIMD16};
    MyAllocator<int> a3{MyAllocatorType::SIMD32};
    MyVector<int> v1{a1};
    MyVector<int> v2{a2};
    MyVector<int> v3{a3};
    v1.resize(2);
    v2.resize(2);
    v3.resize(2);
}
