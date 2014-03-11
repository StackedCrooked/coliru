#include <cstdint>
#include <iterator>
#include <iostream>
#include <vector>


template <typename T>
struct PSAllocator
{
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    template<typename U>
    struct rebind {typedef PSAllocator<U> other;};

    PSAllocator() throw() {};
    PSAllocator(const PSAllocator& other) throw() {}

    template<typename U>
    PSAllocator(const PSAllocator<U>& other) throw() {}

    template<typename U>
    PSAllocator& operator = (const PSAllocator<U>& other) { return *this; }
    PSAllocator<T>& operator = (const PSAllocator& other) { return *this; }
    ~PSAllocator() {}


    pointer allocate(size_type n, const void* hint = 0)
    {
        std::int32_t* data_ptr = reinterpret_cast<std::int32_t*>(::operator new(n * sizeof(value_type)));
        std::cout<<"Allocated: "<<&data_ptr[0]<<" of size: "<<n<<"\n";
        return reinterpret_cast<pointer>(&data_ptr[2]);
    }

    void deallocate(T* ptr, size_type n)
    {
        std::int32_t* data_ptr = reinterpret_cast<std::int32_t*>(ptr);
        std::cout<<"De-Allocated: "<<&data_ptr[-2]<<" of size: "<<n<<"\n";
        ::operator delete(reinterpret_cast<T*>(&data_ptr[-2]));
    }
};


int main()
{
    typedef std::basic_string<char, std::char_traits<char>, PSAllocator<char>> cstring;

    cstring* str = new cstring();
    str->resize(1);
    delete str;

    std::cout<<"\n\n\n\n";

    typedef std::vector<char, PSAllocator<char>> cvector;

    cvector* cv = new cvector();
    cv->resize(1);
    delete cv;
}