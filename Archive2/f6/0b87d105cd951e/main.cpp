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
    template< class U > array_allocator(const array_allocator<U>& other) noexcept(true) = default;
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
    template< class U > array_allocator(const array_allocator<U>& other) noexcept(true) = default;
    ~array_allocator() noexcept(true) {}

    pointer address( reference x ) const noexcept(true) {????;}
    const_pointer address( const_reference x ) const noexcept(true) {????;}
    
    size_type max_size() const noexcept(true) {return (std::allocator<char>()::max_size()-array_offset)/sizeof(n);}
    
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
    void construct(pointer p, Args&&... args ) noexcept(new U(p)(std::forward<Args>(args)...)) 
    {
        rolling_construct(std::integral_constant<int,L>{},*p, std::forward<Args>(args)...);
    }
    void destroy(pointer p) noexcept(true)
    {
        T* begin = *p;
        for(T* cur = begin+L-1; cur --> begin; ) 
            cur->~T();
    }
private:
    template<int count, class First, class... Args >
    void rolling_construct(std::integral_constant<int,count>, T* p, First&& param, Args&&... args)
    {
        new (p)T(std::forward<First>(param));
        rolling_construct(std::integral_constant<int,count-1>{}, ++p, std::forward<First>(args)...);
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
    void rolling_construct(std::integral_constant<int,0>, T* p)
    {
        new (p)T{};
    }
    template<class First, class... Args >
    void rolling_construct(std::integral_constant<int,0>, T* p, First&& param, Args&&... args)
    {
        static_assert(sizeof(First)==0, "too many parameters passed to array constructor");
    }
};



#include <iostream>
#include <string>
using T = std::string[4];
using TA = array_allocator<T>;
using TAT = std::allocator_traits<TA>;

int main()
{
    TA a;
    T * p = TAT::allocate(a, 2);   // allocates space for two T's

    TAT::construct(a, p, "AB", "CDE", "FGHI", "JKLMN");
    TAT::construct(a, p + 1, "OP");

    for (T * q = p; q != p + 2; ++q)
        for (std::string *r = *q; r != *q + 13; ++r)
            std::cout << *r << "\n";

    TAT::destroy(a, p + 1);
    TAT::destroy(a, p);

    TAT::deallocate(a, p, 2);
}