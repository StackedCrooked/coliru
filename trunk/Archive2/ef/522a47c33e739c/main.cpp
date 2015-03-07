#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>


template<typename T>
struct Cow
{
    explicit Cow(T t) : impl(std::make_shared<T>(t)) {}
    
    explicit operator bool() const
    {
        return !!impl;
    }
    
    const T& operator*() const
    {
        return *impl;
    }
    
    const T* operator->() const
    {
        assert(impl);
        return impl.get();
    }
    
    Cow<T> split()
    {
        if (!impl) return Cow<T>(T{});
        return Cow(*impl);
    }
    
    std::size_t use_count() const
    {
        return impl.use_count();
    }
    
    void swap(Cow& rhs)
    {
        using std::swap;
        swap(impl, rhs.impl);
    }
    
private:
    friend std::ostream& operator<<(std::ostream& os, const Cow<T>& cow)
    {
        return os << "Cow { value=" << *cow.impl << " use_count=" << cow.impl.use_count() << ")";
    }
    
    std::shared_ptr<T> impl;
};

    
    #define assert_valid(cond) \
        std::cout << '\n' << __FILE__ << ":"  << __LINE__ << ":" << 4 << ": " << #cond << (cond ? " => PASS" : " => FAIL") << std::endl; \
        assert(cond);
        
    #define assert_use_count(obj, n) \
        std::cout << __FILE__ << ":" << __LINE__ << ":" << 4 << ": " <<   std::flush; \
        std::cout << #obj << ": use_count(" << obj.use_count() << ") == use_count(" << n << ")?" << (obj.use_count() == n ? " => PASS" : " => FAIL") << std::endl; \
        assert(obj.use_count() == n);
        
        

int main()
{
    Cow<std::string> c1("abc");
    std::cout << *c1 << ' ' << c1->size() << std::endl;
    
    assert_valid(c1);
    assert_use_count(c1, 1);
    
    Cow<std::string> c2 = c1;
        
    assert_use_count(c2, 2);
    assert_use_count(c1, 2);
    assert(c2);
    assert(c1);
    
    std::cout << c2 << std::endl;
    assert_use_count(c2, 2);
    
    std::cout << *c2 << std::endl;
    assert_use_count(c2, 2);
    
    auto c3 = c2.split();
    assert_use_count(c1, 2);
    assert_use_count(c2, 2);
    assert_use_count(c3, 1);

    c1 = std::move(c2);
    assert_use_count(c1, 1);
    assert_use_count(c2, 0);
    assert_use_count(c3, 1);
    
    c1 = std::move(c2);
    assert_use_count(c1, 0);
    assert_use_count(c2, 0);
    assert_use_count(c3, 1);
        
    c3 = std::move(c3);
    assert_use_count(c1, 0);
    assert_use_count(c2, 0);
    assert_use_count(c3, 1);
    
    c1 = c2 = c3;
    assert_use_count(c1, 3);
    assert_use_count(c2, 3);
    assert_use_count(c3, 3);
}
