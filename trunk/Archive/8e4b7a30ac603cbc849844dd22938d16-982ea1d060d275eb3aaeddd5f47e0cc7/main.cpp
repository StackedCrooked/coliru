#include <cassert>
#include <new>
#include <iostream>
#include <vector>


struct Item
{    
    using Pool = std::vector<char>;
    
    static Pool& pool()
    {    
        static Pool& fPool = []() -> Pool& {
            static Pool pool;
            pool.reserve(10*sizeof(Item));
            return pool;
        }();
        return fPool;
    }
    
    static std::size_t & delete_count()
    {
        static std::size_t fDeleteCount = 0;
        return fDeleteCount;
    }

    static void* operator new(std::size_t count)
    {        
        assert(count == sizeof(Item));
        if (pool().size() + sizeof(Item) <= pool().capacity())
        {
            std::cout << "Allocating Item on Pool." << std::endl;
            pool().resize(pool().size() + sizeof(Item));
            return &pool().back();
        }
        std::cout << "Pool is full!" << std::endl;
        throw std::bad_alloc();        
    }
    
    static void operator delete(void *) noexcept(true)
    {
        auto itemCount = pool().size() / sizeof(Item);
        assert(delete_count() < itemCount);
        if (++delete_count() == itemCount)
        {
            pool().clear();
            delete_count() = 0;
            std::cout << "Cleared pool." << std::endl;
        }
    }
    
    char data[42];
};


int main()
{
    { Item * item = new Item; delete item; }
    { Item * item = new Item; delete item; }
    
    {
        Item * a = new Item;
        Item * b = new Item;
        delete b;
        Item * c = new Item;
        delete c;
        delete a;
    }
    
    while (new Item);
}
