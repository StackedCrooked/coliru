#include <iostream>

enum thing : unsigned int { NOTHING = 0, TOOTHPICK = 1, PHONE = 2, CAR_KEYS = 4 } ;

struct object_in_hand
{
    object_in_hand() = default ;
    object_in_hand( thing t ) : thing_held(t) {}

    bool is( thing t ) const { return thing_held & t ; }
    void replace( thing t ) { thing_held = t ; }
    void aggregate( thing t ) { thing_held |= t ; }

    private: unsigned int thing_held = NOTHING ;
};

struct player
{
    bool holds( thing t ) const { return object.is(t) ; }
    void pick( thing t ) { object.aggregate(t) ; } // pick without dropping anything
    void repick( thing t ) { object.replace(t) ; } // drop everything and then pick anew
    void drop() { object = NOTHING ; } // drop everything

    private: object_in_hand object ;
};

int main()
{
    player p ;
    std::cout << std::boolalpha
              << p.holds(NOTHING) << ' ' << p.holds(TOOTHPICK) << ' ' << p.holds(PHONE) << ' ' << p.holds(CAR_KEYS) << '\n' ;

    p.pick(PHONE) ;
    std::cout << p.holds(NOTHING) << ' ' << p.holds(TOOTHPICK) << ' ' << p.holds(PHONE) << ' ' << p.holds(CAR_KEYS) << '\n' ;

    p.repick(CAR_KEYS) ; // drop phone, pick car keys
    std::cout << p.holds(NOTHING) << ' ' << p.holds(TOOTHPICK) << ' ' << p.holds(PHONE) << ' ' << p.holds(CAR_KEYS) << '\n' ;

    p.pick(TOOTHPICK) ; // pick toothpick without dropping car keys. (one in each hand, perhaps)?
    std::cout << p.holds(NOTHING) << ' ' << p.holds(TOOTHPICK) << ' ' << p.holds(PHONE) << ' ' << p.holds(CAR_KEYS) << '\n' ;

    p.drop() ; // drop everything. also: p.repick( {} ) ;  or p.repick(NOTHING) ;
    std::cout << p.holds(NOTHING) << ' ' << p.holds(TOOTHPICK) << ' ' << p.holds(PHONE) << ' ' << p.holds(CAR_KEYS) << '\n' ;
}
