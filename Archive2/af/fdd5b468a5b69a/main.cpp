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
        return __atomic_load_n(&t, __ATOMIC_CONSUME);
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



Atomic<int> n;
    
    
int main(int argc, char**)
{
    n = argc;
}