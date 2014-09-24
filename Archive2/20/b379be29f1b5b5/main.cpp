#include <array>
#include <cassert>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
#include <boost/container/static_vector.hpp>


template<typename T, int Capacity = 100>
struct Pool
{
    static Pool<T>& Instance()
    {
        static Pool<T> fInstance;
        return fInstance;
    }



    Pool() : mItems(Capacity)
    {
        for (auto i = mItems.rbegin(), e = mItems.rend(); i != e; ++i)
        {
            Storage* storage = &*i;
            void* ptr = storage;
            mFreed.push_back(static_cast<T*>(ptr));
        }
    }

    T* allocate(std::size_t n)
    {
        assert(n == 1);
        auto result = mFreed.back();
        mFreed.pop_back();
        return result;
    }

    void deallocate(T* t, std::size_t n)
    {
        assert(n == 1);
        mFreed.push_back(t);

    }

    typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type Storage;

    std::vector<T*> mFreed;
    std::vector<Storage> mItems;
};



template <class T>
struct SimpleAllocator
{
    typedef T value_type;

    template<typename U>
    struct rebind
    {
        typedef SimpleAllocator<U> other;
    };

    SimpleAllocator() noexcept
    {
        std::cout << "Pool size: " << sizeof(Pool<T>) << std::endl;
    }

    template <class U>
    SimpleAllocator(const SimpleAllocator<U>& other) noexcept
    {
        std::cout << "Pool size: " << sizeof(Pool<T>) << std::endl;
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


#define TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl

struct Item
{
    Item()  { TRACE(); }
    Item(const Item&)  { TRACE(); }
    Item& operator=(const Item&)   { TRACE();  return *this;}
    Item(Item&&)  { TRACE(); }
    Item& operator=(Item&&)   { TRACE();  return *this;}
    ~Item()   { TRACE(); }

    friend std::ostream& operator<<(std::ostream& os, const Item& item)
    {
        return os << "Item(" << (&item) << ")";

    }
};


int main()
{

    std::promise<int> prom_int{std::allocator_arg_t(), SimpleAllocator<std::promise<void>>()};
    std::promise<long> prom_long{std::allocator_arg_t(), SimpleAllocator<std::promise<void>>()};


    std::vector<std::promise<std::string>> prom_strings;
    prom_strings.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    prom_strings.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    prom_strings.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    prom_strings.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());

    std::cout << "Construct items vector: " << std::endl;
    std::vector<std::promise<Item>> prom_items;
    prom_items.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    prom_items.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    prom_items.emplace_back(std::allocator_arg_t(), SimpleAllocator<std::promise<void>>());
    std::cout << "Finished Constructing items vector" << std::endl;


    auto fut_int = prom_int.get_future();
    auto fut_long = prom_long.get_future();
    auto fut_string0 = prom_strings[0].get_future();
    auto fut_string1 = prom_strings[1].get_future();
    auto fut_string2 = prom_strings[2].get_future();

    auto fut_item0 = prom_items[0].get_future();
    auto fut_item1 = prom_items[1].get_future();
    auto fut_item2 = prom_items[2].get_future();

    std::thread([&]{
        prom_int.set_value(42);
        prom_long.set_value(43);
        prom_strings[0].set_value("0");
        prom_strings[1].set_value("1");
        prom_strings[2].set_value("2");


        std::cout << "\n*** Set Item 0" << std::endl;
        prom_items[0].set_value(Item{});

        std::cout << "\n*** Set Item 1" << std::endl;
        Item item;
        prom_items[1].set_value(item);

        std::cout << "\n*** Set Item 2" << std::endl;
        prom_items[2].set_value(std::move(item));
    }).detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "\n\nGot: " << fut_int.get() << std::endl;
    std::cout << "Got long: " << fut_long.get() << std::endl;
    std::cout << "Got string0: " << fut_string0.get() << std::endl;
    std::cout << "Got string1: " << fut_string1.get() << std::endl;
    std::cout << "Got string2: " << fut_string2.get() << std::endl;

    std::cout << "Got item0: " << fut_item0.get() << std::endl;
    std::cout << "Got item1: " << fut_item1.get() << std::endl;
    std::cout << "Got item2: " << fut_item2.get() << std::endl;
    std::cout << "End of Program\n";
}


