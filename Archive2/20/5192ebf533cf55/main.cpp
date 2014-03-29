#include <memory>
#include <type_traits>

template < typename T, typename A = std::allocator<T> > struct slist
{
    struct node { T value ; node* next ; /* ... */  };
    
    // allocator we would use to allocate nodes
    using slist_allocator = typename A::template rebind<node>::other ;
    
    // an allocator that is compatible (yields compatible pointers etc.)
    // with the allocator we would use to allocate nodes
    using compatible_allocator = typename slist_allocator::template rebind<T>::other ;

    // 'pointer' to T (compatible with the allocator we would use to allocate nodes)
    using compatible_pointer = typename std::allocator_traits<compatible_allocator>::pointer ;
    
    using pointer = typename std::allocator_traits<compatible_allocator>::pointer ;
    
    // the IS (library-wide requirements)specifies that the type of compatible_allocator must be A
    static_assert( std::is_same< A, compatible_allocator >::value,
                   "allocator A does not conform to the library-wide requirements for allocators" ) ;
                   
    // therefore:
    static_assert( std::is_same< pointer, compatible_pointer >::value,
                   "allocator A does not conform to the library-wide requirements for allocators" ) ;
                   
    // ...               
};

template struct slist<int> ;

int main()
{
}
