#include <boost/thread/tss.hpp>
#include <iostream>
#include <string>


namespace test {
template<typename T>
struct ThreadLocal
{
    ThreadLocal()
    {
    }
    
    ThreadLocal(const T& t)
    {
        mPtr.reset(new T(t));
    }
    
    ThreadLocal(T&& t)
    {
        mPtr.reset(new T(std::move(t)));
    }
    
    ThreadLocal& operator=(const T& rhs)
    {
        return *this = T(rhs);
    }
    
    ThreadLocal& operator=(T&& rhs)
    {
        if (T* t = mPtr.get())
        {
            *t = std::move(rhs);
            return *this;
        }
        
        mPtr.reset(new T(std::move(rhs)));
        return *this;
    }
    
    ThreadLocal(const ThreadLocal&) = delete;
    ThreadLocal& operator=(const ThreadLocal&) = delete;
    
    const T* get() const { return mPtr.get(); }
    T* get() { return mPtr.get(); }
    
    const T& operator*() const { if (!mPtr.get()) mPtr.reset(new T()); return *mPtr; }
    T& operator*() { if (!mPtr.get()) mPtr.reset(new T()); return *mPtr; }
    
    T* operator->()
    {
        if (!mPtr.get()) mPtr.reset(new T);
        return mPtr.get();
    }
    
    const T* operator->() const
    {
        if (!mPtr.get()) mPtr.reset(new T);
        return mPtr.get();
    }
    
    friend bool operator==(const ThreadLocal& lhs, const T& rhs)
    {
        if (!lhs.get()) return false;
        return *lhs == rhs;
    }
    
    friend bool operator==(const T& lhs, const ThreadLocal& rhs)
    {
        return rhs == lhs;
    }
    
    friend bool operator<=(const ThreadLocal& lhs, const T& rhs)
    {
        if (!lhs.get()) return false;
        return *lhs <= rhs;
    }
    
    friend bool operator<=(const T& lhs, const ThreadLocal& rhs)
    {
        return rhs <= lhs;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const ThreadLocal& inThreadLocal)
    {
        if (!inThreadLocal.get())
        {
            return os << "ThreadLocal()";
        }
        return os << *inThreadLocal;
    }
    
    mutable boost::thread_specific_ptr<T> mPtr;
};

}



test::ThreadLocal<std::string> s;


int main()
{
    
    s = "abc";
    std::cout << s << std::endl;
    s->resize(4);
    s->back() = 'd';
    std::cout << s << std::endl;
    
    s = std::string("abcdef");
    std::cout << s << std::endl;
    
    std::string e = "e";
    s = e;
    std::cout << s << std::endl;
    
    s = std::move(e);
    std::cout << s << std::endl;
}


