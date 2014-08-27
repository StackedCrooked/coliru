#include <iostream>
#include <vector>
#include <type_traits>

struct parent
{
    virtual ~parent() = default ;

    virtual int mem_fun_parent( int a ) { return i += a ; }

    template < typename DERIVED >
    int mem_fun2_parent( std::vector<DERIVED> children )
    {
        static_assert( std::is_base_of<parent,DERIVED>::value, "class must be derived from parent" ) ;
        int s = 0 ;
        for( DERIVED& d : children ) s += d.mem_fun_parent( d.parent::mem_fun_parent(10) ) ;
        return s ;
    }

    private : int i = 5 ;
};

struct child : parent { /* ... */ };

int main()
{
    std::vector<child> children(100) ;
    parent p ;
    std::cout << p.mem_fun2_parent(children) << '\n' ;
}
