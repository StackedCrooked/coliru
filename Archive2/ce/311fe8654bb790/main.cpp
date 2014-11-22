#include <iostream>

struct mover
{
    explicit constexpr mover( int s ) : speed_(s) {}
    int speed_ = 0 ;
    constexpr int speed() const { return speed_ ; }
    /* ... */
};
struct walker : mover { explicit constexpr walker( int w = 2 ) : mover(w) {} ; /* ... */ };
struct runner : mover { explicit constexpr runner( int r = 6 ) : mover(r) {} ; /* ... */ };
struct flier : mover { explicit constexpr flier( int f = 20 ) : mover(f) {} ; /* ... */ };
struct swimmer : mover { explicit constexpr swimmer( int s = 1 ) : mover(s) {} ; /* ... */ };

template < typename T > struct usually : T
{
    usually() = default ;
    constexpr usually( int s ) : T(s) {} ;
    constexpr int normal_speed() const { return T::speed() ; }
};

struct animal { /* ... */ };
struct human : animal, usually<walker>, runner, swimmer { /* ... */ };
struct cheetah : animal, usually<runner>, swimmer, walker { /* ... */ };
struct bluejay : animal, usually<flier>, walker { /* ... */ };
struct trout : animal, usually<swimmer> { /* ... */ };

int main()
{
    human h ;
    std::cout << h.normal_speed() << ' ' << h.runner::speed() << '\n' ;

    bluejay b ;
    std::cout << b.normal_speed() << ' ' << b.walker::speed() << '\n' ;
}
