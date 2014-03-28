#include <memory>
#include <type_traits>

template < typename T, typename Alloc = std::allocator<T> > struct slist
{
    struct node { T value ; node* next ; /* ... */  };
    
    // allocator we would use to allocate nodes
    using slist_allocator = typename Alloc::template rebind<node>::other ;
    
    // 'pointer' to node (compatible with the allocator we would use to allocate nodes)
    using pointer_to_node = typename slist_allocator::pointer ;
    
    // an allocator that is compatible (yields compatible pointers etc.)
    // with the allocator we would use to allocate nodes
    using compatible_allocator = typename slist_allocator::template rebind<T>::other ;

    // 'pointer' to T (compatible with the allocator we would use to allocate nodes)
    using compatible_pointer_to_T = typename std::allocator_traits<compatible_allocator>::pointer ;
    
    // 'pointer to T (compatible with Alloc)
    using pointer = typename std::allocator_traits<Alloc>::pointer ;
    
    // the IS (library-wide requirements)requires that the type of compatible_allocator must be Alloc
    static_assert( std::is_same< Alloc, compatible_allocator >::value,
                   "allocator Alloc does not conform to the library-wide requirements for allocators" ) ;
                   
    // therefore:
    static_assert( std::is_same< pointer, compatible_pointer_to_T >::value,
                   "allocator Alloc does not conform to the library-wide requirements for allocators" ) ;
                   
    // ...               
};

template struct slist<int> ;

int main()
{
}
