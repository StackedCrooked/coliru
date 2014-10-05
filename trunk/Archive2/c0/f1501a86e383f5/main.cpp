#include <iostream>
#include <functional>

struct monster {
    virtual ~monster() = default;
};

////////////// header attack_mediator.h ////////////////
struct wizard ;

struct attack_mediator {
    static int bonus( const wizard& w, const monster& m ) ;
    static int immunity_period( const wizard& w, const monster& m ) ;
    // ...
};
//////////////////////////////////////////////////////////////


struct wizard {
    const enum school_t { Enchantment, Conjuration, Illusion } school ;
	const char* school_name() const {
	    static const char* const name[] { "Enchantment", "Conjuration", "Illusion" } ;
	    return name[school] ;
	}

	wizard( school_t s ) : school(s) {}

	void attack ( monster& m ) {
		std::cout << "wizard (" << school_name() << ") <-> " << typeid(m).name() + 1 ; // +1 for GNU

		const int bonus = attack_mediator::bonus( *this, m ) ;
		if(bonus) std::cout << " + bonus " << bonus ;

		const int immunity = attack_mediator::immunity_period( *this, m ) ;
		if(immunity) std::cout << " + immune for first " << immunity << " minutes." ;

		std::cout << '\n' ;
	}
};

struct goblin : monster {};
struct snake : monster {};
struct dragon : monster {};

////////////// implementation attack_mediator.cc ////////////////
#include <typeindex>
#include <map>

namespace
{
    struct attatck_attributes { int bonus ; int immunity ; } ;
    static const std::map< std::pair< wizard::school_t, std::type_index >, attatck_attributes > attributes_map =
    {
        { { wizard::Enchantment, typeid(goblin) }, { 1, 0 } },
        { { wizard::Enchantment, typeid(dragon) }, { 6, 5 } },
        { { wizard::Illusion, typeid(goblin) }, { 2, 0 } },
        { { wizard::Illusion, typeid(snake) }, { 1, 0 } },
        { { wizard::Conjuration, typeid(snake) }, { 3, 10 } }
    };
}

int attack_mediator::bonus( const wizard& w, const monster& m ) {
    const auto iter = attributes_map.find( { w.school, typeid(m) } ) ;
    return iter != attributes_map.end() ? iter->second.bonus : 0 ;
}

int attack_mediator::immunity_period( const wizard& w, const monster& m ) {
    const auto iter = attributes_map.find( { w.school, typeid(m) } ) ;
    return iter != attributes_map.end() ? iter->second.immunity : 0 ;
}
////////////////////////////////////////////////////////////////////

int main()
{
     wizard wizards[] { wizard::Conjuration, wizard::Enchantment, wizard::Illusion } ;

     goblin g ; snake p ; dragon d ;
     std::reference_wrapper<monster> monsters[] { g, p, d } ;

     for( wizard& w : wizards ) {
         for( auto m : monsters ) w.attack(m) ;
         std::cout << '\n' ;
     }
}
