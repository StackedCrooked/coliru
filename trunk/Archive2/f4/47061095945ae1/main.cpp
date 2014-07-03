#include <memory>
#include <type_traits>

#ifdef _MSC_VER
#define noexcept(X) throw()
#endif

template<class T>
struct alias {
    typedef T type;
};

template <typename T>
struct array_allocator : std::allocator<T> 
{    
    template< class U > struct rebind { typedef array_allocator<U> other; };
    
    array_allocator() = default;
    array_allocator(const array_allocator& other) = default;
    template< class U > array_allocator(const array_allocator<U>&) noexcept(true) {}
};

template <typename T, size_t L>
struct array_allocator<T[L]>
{
    typedef typename alias<T[L]>::type  value_type;
    typedef value_type*                 pointer;
    typedef const value_type*           const_pointer;
    typedef value_type&                 reference;
    typedef const value_type&           const_reference;
    typedef std::size_t                 size_type;
    typedef std::ptrdiff_t              difference_type;
    typedef std::true_type              propagate_on_container_move_assignment;
    template< class U > struct rebind { typedef array_allocator<U> other; };
    
    array_allocator() = default;
    array_allocator(const array_allocator& other) = default;
    template< class U > array_allocator(const array_allocator<U>&) noexcept(true) {}
    ~array_allocator() noexcept(true) {}

    pointer address( reference x ) const noexcept(true) {return &x;}
    const_pointer address( const_reference x ) const noexcept(true) {return &x;}
    
    size_type max_size() const noexcept(true) {return (std::allocator<char>{}.max_size())/sizeof(value_type);}
    
    template<class U, class... Args> void construct( U* p, Args&&... args ) noexcept(rebind<U>::other::construct(p, std::forward<Args>(args)...)) {rebind<U>::other::construct(p, std::forward<Args>(args)...);}
    template<class U> void destroy(U* p) noexcept(true) {rebind<U>::other::destroy(p);}

    pointer allocate(size_type n, std::allocator<void>::const_pointer hint=0)
    {
        T* buffer = std::allocator<T>{}.allocate(n*L, hint);
        return reinterpret_cast<pointer>(buffer);
    }
    void deallocate(pointer p, size_type n) noexcept(true) 
    {
        T* buffer = reinterpret_cast<T*>(p);
        std::allocator<T>{}.deallocate(buffer, n*L);
    }
    template<class... Args >
    void construct(pointer p, Args&&... args )
    {
        static_assert(sizeof...(args)<=L, "too many parameters passed to array constructor");
        rolling_construct(std::integral_constant<int,L-1>{},*p, std::forward<Args>(args)...);
    }
    void destroy(pointer p) noexcept(true)
    {
        T* begin = *p;
        for(T* cur = begin+L; cur --> begin; ) 
            cur->~T();
    }
private:
    template<int count, class First, class... Args >
    void rolling_construct(std::integral_constant<int,count>, T* p, First&& param, Args&&... args)
    {
        new (p)T(std::forward<First>(param));
        rolling_construct(std::integral_constant<int,count-1>{}, ++p, std::forward<Args>(args)...);
    }
    template<int count, class First, class... Args >
    void rolling_construct(std::integral_constant<int,count>, T* p, First&& param)
    {
        new (p)T(std::forward<First>(param));
        rolling_construct(std::integral_constant<int,count-1>{}, ++p);
    }
    template<int count, class... Args >
    void rolling_construct(std::integral_constant<int,count>, T* p)
    {
        new (p)T{};
        rolling_construct(std::integral_constant<int,count-1>{}, ++p);
    }
    //end cases
    template<class First>
    void rolling_construct(std::integral_constant<int,0>, T* p, First&& param)
    {
        new (p)T(std::forward<First>(param));
    }
    void rolling_construct(std::integral_constant<int,0>, T* p)
    {
        new (p)T{};
    }
};



#include <iostream>

struct announcer {
    announcer() {std::cout << "def ctor: " << this << '\n';}
    announcer(const char* r) {std::cout << "cnv ctor: " << this << " from " << r << '\n';}
    announcer(const announcer& r) {std::cout << "cpy ctor: " << this  << " from " << &r << '\n';}
    announcer& operator=(const announcer& r) {std::cout << "cpy asn: " << this  << " from " << &r << '\n'; return *this;}
    ~announcer() {std::cout << "    dtor: " << this << '\n';}
    friend std::ostream& operator<<(std::ostream& out, const announcer& data) {return out << "     out: " << &data;}
};

using T = announcer[4];
using TA = array_allocator<T>;
using TAT = std::allocator_traits<TA>;

int main()
{
    TA a;
    T * p = TAT::allocate(a, 2);   // allocates space for two T's

    TAT::construct(a, p, "AB", "CDE", "FGHI", "JKLMN");
    TAT::construct(a, p + 1, "OP");

    for (T * q = p; q != p + 2; ++q)
        for (auto r = *q; r != *q + 4; ++r)
            std::cout << *r << "\n";

    TAT::destroy(a, p + 1);
    TAT::destroy(a, p);

    TAT::deallocate(a, p, 2);

    return 0;
}