#include <iostream>
#include <memory>

template < typename T, typename ALLOCATOR = std::allocator<T> > struct colony
{
    struct group { group( int, double ) {} /* .. */ };

    explicit colony( const ALLOCATOR& a = ALLOCATOR() ) : the_allocator(a)
    {
        // type of rebound allocator
        using rebound_alloc_type = typename std::allocator_traits<ALLOCATOR>::template rebind_alloc<group> ;

        // create an object of type rebound allocator
        rebound_alloc_type rebound_allocator(the_allocator) ;

        // use the allocator object
        group* first_group = std::allocator_traits<rebound_alloc_type>::allocate( rebound_allocator, 1 ) ;
        std::allocator_traits<rebound_alloc_type>::construct( rebound_allocator, first_group, 12, 34.56 ) ;
        std::cout << "group* first_group == " << first_group << '\n' ;
        // etc.

        // ...
    }

    // ...

    private:
        ALLOCATOR the_allocator ;
        group* ptr = nullptr ;
};

int main()
{
    colony<int> c ;
}
