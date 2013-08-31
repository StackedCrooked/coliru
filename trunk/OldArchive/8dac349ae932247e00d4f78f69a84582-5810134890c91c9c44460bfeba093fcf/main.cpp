template<typename T>
struct propagate_ptr {
    explicit propagate_ptr(T* value)
        : value(value)
    {}
        
    using element_type = T;
    
    T& operator*() { return *value; }
    T const& operator*() const { return *value; }
    T* operator->() { return value; }
    T const* operator->() const { return value; }
    
private:
    T* value;
};

template<typename T>
propagate_ptr<T> make(T* p)
{ return propagate_ptr<T> { p }; }

struct foo {
    propagate_ptr<propagate_ptr<propagate_ptr<int>>> p;
    
    int& value()
    { return ***p; }
    
// Change 0 to 1 to see compiler in action
#if 0
    // Caught by the compiler:
    int /* non-const! */& value() const
    { return ***p; }
    
#else
    // Correct:
    int const& value() const
    { return ***p; }
#endif
};

#include <cassert>

int main()
{
    int i = 0;
    auto pi = make(&i);
    auto ppi = make(&pi);
    foo const f { make(&ppi) };
    assert( &f.value() == &i );
}