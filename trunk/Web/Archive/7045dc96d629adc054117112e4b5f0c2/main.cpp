#include <string>
#include <mutex>

template<typename T>
struct safe {
    template<typename ...Args>
    safe(Args && ...args) : t(std::forward<Args>(args)...) {}
    
    typedef std::unique_lock<std::mutex> lock_;
    struct lock : lock_ {
        lock(std::mutex& m, T & t) : lock_(mtx), t(&t) {}
        lock(lock&&) = default;
        const T * operator->() const { return t; }
        T * operator->() { return t; }
        T * t;
    };
    
    lock operator->() { return lock(mtx, t); }
    
private:
    mutable std::mutex mtx;
    T t;
};

struct item {};
int main()
{
    safe<std::string> item("abc");;    
    item->clear();    
}