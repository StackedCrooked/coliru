#include <vector>
#include <utility>

template <class T>
class is_allocator
{
    typedef char yes;
    typedef long no;

    // you can extend this with many more checks on the allocator interface
    template <class C> static yes check( decltype(std::declval<C>().allocate(0)) );
    
    template <class C> static no  check(...);
public:
    enum { value = sizeof(check<T>(0)) == sizeof(yes) };
};

int main()
{
    std::vector<int> v { 1, 2 };
    using V = decltype(v)::value_type;
    using A = decltype(v)::allocator_type;
    static_assert(!is_allocator<V>::value, "");
    static_assert( is_allocator<A>::value, "");
}
