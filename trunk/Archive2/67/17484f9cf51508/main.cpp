#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <assert.h>
#include <stdint.h>


template<typename T>
class Atomic
{
public:
    Atomic(T t = T()) : t(t)
    {
        assert(__atomic_is_lock_free(sizeof(T), nullptr));
    }
    
    // disable copy construction and copy-assigment
    Atomic(const Atomic&) = delete;
    Atomic& operator=(const Atomic&) = delete;
    
    // get the current value
    T load() const
    {
        return __atomic_load_n(&t, __ATOMIC_ACQUIRE);
    }   
    
    // set a new value
    void store(T new_value)
    {
        __atomic_store_n(&t, new_value, __ATOMIC_RELEASE);
    }
    
    void operator=(T new_value)
    {
        store(new_value);
    } 
    
    operator T() const
    {
        return load();
    }
    
    // pre-increment
    T operator++()
    {
        return __atomic_add_fetch(&t, 1, __ATOMIC_ACQ_REL);
    }
    
    // post-increment
    T operator++(int)
    {
        return __atomic_fetch_add(&t, 1, __ATOMIC_ACQ_REL);
    }
    
private:
    mutable T t;
};


int main()
{
    Atomic<int> n;
    //int n = 0; // test with non-atomic
    
//    std::cout << "n = " << n << std::endl;
//    std::cout << "++n = " << ++n << std::endl;
//    std::cout << "n++ = " << n++ << std::endl;

    auto num_threads = 4;
    auto num_iterations = 100000;

    std::vector<std::thread> threads;
    for (int i = 0; i != num_threads; ++i)
    {
        threads.push_back(std::thread([&]{
            for (int i = 0; i != num_iterations; ++i) {
                n++;
            }
        }));
    }
    
    for (auto& t : threads)
    {
        t.join();
    }
    
    std::cout << n << std::endl;
}