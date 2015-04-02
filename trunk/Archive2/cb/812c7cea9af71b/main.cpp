#include <array>
#include <atomic>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>


struct TaggedPtr
{   
    TaggedPtr() = default;
    
    explicit TaggedPtr(void* p) : data_(reinterpret_cast<uintptr_t>(p))
    {
    }

    uint16_t get_metadata() const { return data_ >> 48; }

    void set_metadata(uint16_t v)
    {
        uintptr_t ip = reinterpret_cast<uintptr_t>(get());
        ip |= static_cast<uintptr_t>(v) << 48;
        data_ = ip;
    }

    void* get() const
    {
        return reinterpret_cast<void*>(data_ & ((1ULL << 48) - 1));
    }

    friend bool operator==(TaggedPtr lhs, TaggedPtr rhs)
    {
        return lhs.get() == rhs.get();
    }

    uintptr_t data_;
};

std::array<char, 150> storage;
std::atomic<int> storage_offset;


// Task size is only one pointer.
// Actual contents:
// - 48-bit pointer data
// - 16-bit index to storage
struct Task
{
    using FPtr = void (*) (void*);
    
    Task() = default;
    
    explicit Task(FPtr fptr, uint16_t storage_index) : fptr_(reinterpret_cast<void*>(fptr))
    {
        fptr_.set_metadata(storage_index);
    }
    
    void operator()()
    {
        uint16_t storage_index = fptr_.get_metadata();
        void* storage_ptr = &storage[storage_index];        
        reinterpret_cast<FPtr>(fptr_.get())(storage_ptr);
    }
    
    TaggedPtr fptr_;
};


std::array<Task, 100> tasks;
std::atomic<int> tasks_offset;


template<typename F>
uint16_t alloc(F f)
{
    auto f_size = sizeof(f);    
    int storage_in_use = storage_offset.fetch_add(f_size);
    if (storage_in_use + f_size > storage.size())
    {
        std::cout << " [!] (storage_in_use(" << storage_in_use << ") + f_size(" << f_size << ")) > storage.size(" << storage.size() << ")  => consume the queue!" << std::endl;
        int num_tasks = tasks_offset;
        for (auto i = 0; i != num_tasks; ++i)
        {
            tasks[i]();
        }
        
        tasks_offset = 0;
        storage_offset = storage_in_use = 0;
        std::cout << " [*] All tasks are done." << std::endl << std::endl;
        
    }
    else
    {
        std::cout << " [+] Added task of size " << f_size << " to the queue." << std::endl;
    }
    auto memory = &storage[storage_in_use];
    new (memory) F(std::move(f));
    return storage_in_use;
}


template<typename F>
void post_impl(F f)
{
    auto storage_index = alloc(f);
    
    // this instantiation generates a new function
    // we get the function pointer and use 
    auto function_pointer = +[](void* storage) { static_cast<F*>(storage)->operator()(); };
    
    tasks[tasks_offset++] = Task(function_pointer, storage_index);
}


template<typename F>
void post(F f)
{
    
    post_impl([f]{f();});
}


void test_function() { std::cout << "test_function succeeded" << std::flush; }



int main()
{
    for (int i = 0; i != 100; ++i)
    {
        post([]{ std::cout << "Empty task" << std::endl; });
     
        post([i]{ std::cout << "i=" << i << std::endl; });
        
        long j = 43;
        post([i, j]{ std::cout << "i+j=" << (i + j) << std::endl; });
        
        double d = 44.45;
        post([i, j, d]{ std::cout << "i+j+d=" << (i + j + d) << std::endl; });
        
        long double ld = 88.99;
        post([i, j, d, ld]{ std::cout << "i+j+d+ld=" << (i + j + d + ld) << std::endl; });
        
        char c = 'a';
        post([i, j, d, ld, c]{ std::cout << "i+j+d+ld+c=" << (i + j + d + ld + c) << std::endl; });
        
        char cc = 'b';
        post([i, j, d, ld, c, cc]{ std::cout << "i+j+d+ld+c+cc=" << (i + j + d + ld + c + cc) << std::endl; });
        
        post([]{});
        
        post(+[]{});
        
        post(&test_function);
        
    }
    for (auto& task : tasks)
    {
        task();
    }
}