#include <array>
#include <atomic>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>


struct Task
{
    using FunctionPointer = void (*) (void*);    
    Task() : fptr_([](void*){}), storage_() {}    
    Task(FunctionPointer fptr, void* storage) : fptr_(fptr), (storage) { }    
    void operator()() { fptr_(storage_); }
    FunctionPointer fptr_;
    void* storage_;
};


std::array<char, 1000> storage;
std::atomic<int> storage_offset;

std::array<Task, 100> tasks;
std::atomic<int> tasks_offset;


template<typename F>
void* alloc(F f)
{
    auto size = sizeof(f);
    int index = storage_offset.fetch_add(size);
    assert(index + size <= storage.size());
    auto memory = &storage[index];
    new (memory) F(std::move(f));
    return memory;
}


template<typename F>
void post(F f)
{
    void* data_storage = alloc(f);    
    

    // type-erasure happens here!
    Task::FunctionPointer function_pointer = [](void* storage) {
        (*static_cast<F*>(storage))();
    };
    tasks[tasks_offset++] = Task(function_pointer, data_storage);
}


void test_function() { std::cout << "test_function succeeded" << std::flush; }



int main()
{
    post([]{ std::cout << "Empty task"; });

    int i = 42;
    post([i]{ std::cout << "i=" << i; });

    long j = 43;
    post([i, j]{ std::cout << "i+j=" << (i + j); });

    double d = 44.45;
    post([i, j, d]{ std::cout << "i+j+d=" << (i + j + d); });

    long double ld = 88.99;
    post([i, j, d, ld]{ std::cout << "i+j+d+ld=" << (i + j + d + ld); });

    char c = 'a';
    post([i, j, d, ld, c]{ std::cout << "i+j+d+ld+c=" << (i + j + d + ld + c); });

    char cc = 'b';
    post([i, j, d, ld, c, cc]{ std::cout << "i+j+d+ld+c+cc=" << (i + j + d + ld + c + cc); });

    post([]{});

    post(+[]{});

    post(&test_function);


    for (auto& task : tasks)
    {
        task();
    }
}
