#include <iostream>
#include <algorithm>
#include <memory>
#include <cstddef>

template <typename T>
struct dynarray
{
private:    
    std::unique_ptr<T[]> store;
    size_t length;
    
public:    
        
    operator bool() const noexcept
    {
        return static_cast<bool>(store);
    }
    
    T& operator[](size_t i)
    {
        return store[i];
    }
    const T& operator[](size_t i) const
    {
        return store[i];
    }
    
    T* data()
    {
        return store.get();
    }
    
    const T* data() const
    {
        return store.get();
    }
    
    size_t size() const
    {
        return length;
    }
    
    T* begin()
    {
        return data();
    }
    const T* begin() const
    {
        return data();
    }
    
    T* end()
    {
        return data() + size();
    }
    const T* end() const
    {
        return data() + size();
    }    

    dynarray():
        store(nullptr),
        length(0)
    {}

    dynarray(size_t size):
        store(new T[length]),
        length(length)
    {}
    
    dynarray(const dynarray<T>& xs):
        store(new T[xs.length]),
        length(xs.length)
    {
        std::copy(xs.begin(), xs.end(), begin());
    }
    
    dynarray(dynarray<T>&& xs) noexcept:
        store(std::move(xs.store)),
        length(xs.length)
    {
        xs.length = 0;
    }
    
    dynarray& operator=(const dynarray<T>& xs)
    {
        store.reset(new T[xs.length]);
        std::copy(xs.begin(), xs.end(), begin());
        length = xs.length;
        return *this;
    }
};

int main()
{
}