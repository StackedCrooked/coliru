#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <future>
#include <type_traits>
#include <thread>
#include <utility>


template<typename T>
struct Pool
{
    static Pool<T>& Instance()
    {
        static Pool<T> fInstance;
        return fInstance;
    }
    
    Pool() : mItems(100) {}
    
    T* allocate(std::size_t n)
    {
        if (mUsed + n > mItems.capacity())
        {
            mItems.resize(mUsed + n);
        }
        auto result = &mItems[mUsed];
        mUsed += n;
        return static_cast<T*>(static_cast<void*>(result));
    }
    
    void deallocate(T* t, std::size_t n)
    {
        auto it = std::find_if(mItems.rbegin(), mItems.rend(), [t](const Storage* storage) {
            return static_cast<void*>(storage) == static_cast<void*>(t);
        });
        if (it == mItems.end())
        { 
            std::abort();
        }
        
        mItems.erase(it, it + n);
        
        
        mFreed += n;
        if (mUsed == mFreed)
        {
            mUsed = mFreed = 0;
        }
    }
    
    typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type Storage;
    
    std::vector<Storage> mItems;
    uint32_t mInitialSize = 0;
    uint32_t mCapacity = 100;
    uint32_t mUsed = 0;
    uint32_t mFreed = 0;
};



template <class T>
struct SimpleAllocator
{
typedef T value_type;

SimpleAllocator() noexcept
{
}

template <class U>
SimpleAllocator(const SimpleAllocator<U>& other) noexcept
{
}

T* allocate(std::size_t n) noexcept
{   
    return Pool<T>::Instance().allocate(n);
}

void deallocate(T* t, std::size_t n) noexcept
{
    Pool<T>::Instance().deallocate(t, n);
}
};


template <class T, class U> bool operator==(const SimpleAllocator<T>&, const SimpleAllocator<U>&)  noexcept{ return true; }
template <class T, class U> bool operator!=(const SimpleAllocator<T>& t, const SimpleAllocator<U>& u)  noexcept { return !(t == u); }



int main()
{
std::promise<int> prom_int{std::allocator_arg_t(), SimpleAllocator<std::promise<void>>()};
std::promise<long> prom_long{std::allocator_arg_t(), SimpleAllocator<std::promise<void>>()};
std::promise<std::string> prom_string{std::allocator_arg_t(), SimpleAllocator<std::promise<void>>()};


auto fut_int = prom_int.get_future();
auto fut_long = prom_long.get_future();
auto fut_string = prom_string.get_future();

std::thread([&]{
    prom_int.set_value(42);
    prom_long.set_value(42000);
    prom_string.set_value("abcdefghijkl");
}).detach();


std::cout << "Got: " << fut_int.get() << std::endl;    
std::cout << "Got long: " << fut_long.get() << std::endl;    
std::cout << "Got string: " << fut_string.get() << std::endl;
}


