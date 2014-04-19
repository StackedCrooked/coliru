#include <iostream>
#include <initializer_list>
#include <string>
#include <utility>

template < typename T > struct list
{
    using value_type = T ;
    // many more typedefs
    
    list() = default ;
    list( std::initializer_list<T> il ) { for( const auto& v : il ) push_back(v) ; }
    // other foundation operators
    
    bool empty() const { return sz == 0 ; }
    // other inspectors
    
    void push_back( const T& v ) 
    {
        if( empty() ) first = last = new node(v) ;
        else
        {
            last->next = new node( v, last ) ;
            last = last->next ;
        }
        ++sz ;
    }
    
    template < typename CALLABLE > void for_each( CALLABLE fn ) const 
    { for( auto p = first ; p ; p = p->next ) fn( const_cast<T&>(p->value) ) ; }
   
    template < typename CALLABLE > void for_each( CALLABLE fn )
    { for( auto p = first ; p ; p = p->next ) fn(p->value) ; }
    
   // many more member functions
   
   
   private: 
        struct node
        {
            explicit node( const T& v ) : value(v) {}
            explicit node( const T& v, node* p, node* n = nullptr ) : value(v), next(n), prev(p) {} 
            T value ;
            node* next= nullptr ;
            node* prev = nullptr ;
        };
        
        node* first = nullptr ;
        node* last = nullptr ;
        std::size_t sz = 0 ;
}; 

int main()
{
    // class with three data types
    struct A { int i ; std::string str ; double d ; /* more member variables */ };
    
    list<A> lst { { 0, "zero", 0.12 }, { 1, "one", 1.23 }, { 2, "two", 2.34 } } ;
    lst.push_back( { 3, "three", 3.45 } ) ;
    
    lst.for_each( []( const A& a ) { std::cout << '{' << a.i << ',' << a.str << ',' << a.d << "} " ; } ) ;
    std::cout << '\n' ;
    
    list< std::pair< int, char > > another_list ; // list of template class with two data types
    another_list.push_back( { 99, '*' } ) ;
    // etc.
}

