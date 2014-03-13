#include <iostream>
#include <memory>
#include <utility>
#include <cassert>

struct monster {
    virtual ~monster() = default ;

    virtual int attacks() const = 0 ;
	// etc.
};

template < typename DERIVED, int NATTACKS > struct monster_type : monster {
    static int numberOfAttacks ;
    virtual int attacks() const override { return numberOfAttacks ; }
    // etc.
};

template < typename DERIVED, int NATTACKS >
int monster_type<DERIVED,NATTACKS>::numberOfAttacks = NATTACKS ;
// etc.

struct goblin: monster_type<goblin,5> {};
struct dragon: monster_type<dragon,20> { dragon(double,int) {} };
struct troll: monster_type<troll,8> { explicit troll(int) {} };

namespace cpp14
{
    template< class T, typename... ARGS >
    std::unique_ptr<T> make_unique( ARGS&&... args )
    { return std::unique_ptr<T>( new T( std::forward<ARGS>(args)... ) ) ; }
}

int main()
{
    using cpp14::make_unique ;
    std::unique_ptr<monster> monsters[] = {
        make_unique<goblin>(), make_unique<dragon>( 3.4, 7 ), make_unique<troll>(24) } ;

   for( const auto& pointer : monsters ) std::cout << pointer->attacks() << ' ' ;
   assert( dragon::numberOfAttacks == 20 && "something is wrong" ) ;
}
