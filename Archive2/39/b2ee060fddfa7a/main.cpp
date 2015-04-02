#include <array>
#include <atomic>
#include <cassert>
#include <vector>


std::array<char, 1000> storage;
std::atomic<int> offset;

using FPtr = void(*)(void*);


struct Task
{
    explicit Task(FPtr fptr, void* storage) : fptr(fptr), storage(storage) {}
    
    void operator()()
    {
        fptr(storage);
    }
    
    FPtr fptr;
    void* storage;
};

std::vector<Task> tasks;


template<typename Task>
void execute_task(void* storage_for_task)
{
    Task& task = *static_cast<Task*>(storage_for_task);
    task();
}


template<typename F>
void* alloc(F f)
{
    auto size = sizeof(f);    
    int index = offset.fetch_add(size);
    assert(index + size <= storage.size());
    auto memory = &storage[index];
    new (memory) F(std::move(f));
    return memory;
}


template<typename F>
void post(F f)
{
    void* storage = alloc(f);
    FPtr fptr = &execute_task<F>;
    tasks.push_back(Task(fptr, storage));
}


#include <iostream>


int main()
{
    for (int i = 0; i != 10; ++i)
    {
        std::cout << "Allocating task " << i << std::endl;
        post([i]{ std::cout << i << std::endl; });
    }
    
    
    for (auto& task : tasks)
    {
        std::cout << "Running task " << (&task - &*tasks.begin()) << std::endl;
        task();
    }
}