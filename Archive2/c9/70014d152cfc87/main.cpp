#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <string.h>


//! { T + char array inline }
template<typename T>
struct Inline
{
    template<typename ...Args>
    Inline(std::size_t n, Args&& ...args)
    {
        mData.resize(sizeof(T) + n);
        new (&mData[0]) T(std::forward<Args>(args)...);
    }
    
    Inline(Inline&& rhs)
    {
        *this = std::move(rhs);
    }
    
    Inline(const Inline& rhs)
    {
        *this = rhs;
    }
    
    Inline& operator=(const Inline& rhs)
    {
        mData = rhs.mData;
        get() = rhs.get();
        return *this;
    }
    
    Inline& operator=(Inline&& rhs)
    {
        T local = std::move(rhs.get());
        mData = std::move(rhs.mData);
        new (&mData[0]) T(std::move(local));
        return *this;
    }
    
    T& get()    
    {
        return *static_cast<T*>(static_cast<void*>(data()));
    }
    
    const T& get() const
    {
        return *static_cast<const T*>(static_cast<const void*>(data()));
    }
    
    void resize(std::size_t n)
    {
        if (n > mData.size())
        {
            Inline<T> local(n, get());
            memcpy(local.data(), data(), size());
            *this = std::move(local);
            return;
        }
        
        mData.resize(sizeof(T) + n);
    }

    std::size_t size() const
    {
        return mData.size() - sizeof(T);
    }
    
    const char* data() const
    {
        return mData.data() + sizeof(T);
    }
    
    char* data()
    {
        return &mData[0] + sizeof(T);
    }
    
private:
    std::string mData;
};


int main()
{
    Inline<int> cb(10, 1);
    std::cout << cb.get() << std::endl;
    std::cout << cb.size() << std::endl;
    cb.resize(11);
    std::cout << cb.size() << std::endl;
}
