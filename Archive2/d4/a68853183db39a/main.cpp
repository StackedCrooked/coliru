#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <memory>

// http://en.cppreference.com/w/cpp/memory/enable_shared_from_this
struct object : std::enable_shared_from_this<object>
{
    using pointer = std::shared_ptr<object> ;
    static pointer create( /* ... */ ) { return pointer( new object( /* ... */  ) ) ; }

    // http://en.cppreference.com/w/cpp/memory/enable_shared_from_this/shared_from_this
    // use std::addressof if the actual afress is required
    pointer operator& () { return shared_from_this() ; }

    ~object() { objects.erase(this) ; }

    void paint()
    {
        if( !painted )
        {
            std::cout << "paint { object #" << id << " at " << this << " }\n" ;
            painted = true ;
        }
    }

    void refresh() { painted = false ; }
    static void refresh_all() { for_each( &object::refresh ) ; }

    static void for_each( std::function< void(object*) > fn )
    { for( auto p : objects ) fn(p) ; }

    private:
        object( /* ... */ ) : id(cnt++) { objects.insert(this) ; }

        object( const object& ) = delete ;
        // object& operator= ( const object& ) = delete ; // implicitly deleted

        const int id ;
        bool painted = false ;

        static std::set<object*> objects ;
        static int cnt ;

};

std::set< object* > object::objects ;
int object::cnt = 0 ;

int main()
{
    std::vector< object::pointer > seq_one ;
    for( int i = 0 ; i < 8 ; ++i ) seq_one.push_back( object::create() ) ;

    std::vector< object::pointer > seq_two { seq_one[0], seq_one[3], seq_one[6], seq_one[3], seq_one[6] };
    std::vector< object::pointer > seq_three { seq_one[5], seq_one[2], seq_one[3], seq_one[6], seq_one[0] };

    for( object::pointer p : seq_two ) p->paint() ;
    for( object::pointer p : seq_three ) p->paint() ;
    for( object::pointer p : seq_one ) p->paint() ;
    std::cout << "---------------------------\n" ;
    
    object::refresh_all() ; // now we can paint all the objects again
    
    seq_one.push_back( object::create() ) ;
    seq_two.push_back( object::create() ) ;
    seq_three.push_back( seq_two.front() ) ;

    // ...
    for( object::pointer p : seq_two ) p->paint() ;
    for( object::pointer p : seq_three ) p->paint() ;
    for( object::pointer p : seq_one ) p->paint() ;
    std::cout << "---------------------------\n" ;
}
