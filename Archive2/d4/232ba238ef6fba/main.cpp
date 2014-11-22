#include <iostream>
#include <functional>

struct moves
{
    explicit constexpr moves( int s ) : speed_(s) {}
    int speed_ = 0 ;
    constexpr int speed() const { return speed_ ; }
    /* ... */
};

struct walks : moves { explicit constexpr walks( int w = 2 ) : moves(w) {} ; /* ... */ };
struct runs : moves { explicit constexpr runs( int r = 6 ) : moves(r) {} ; /* ... */ };
struct flies : moves { explicit constexpr flies( int f = 20 ) : moves(f) {} ; /* ... */ };
struct swims : moves { explicit constexpr swims( int s = 1 ) : moves(s) {} ; /* ... */ };

struct animal { virtual ~animal() = default ; virtual int normal_speed() const = 0 ;  /* ... */ };

template < typename T > struct usually : virtual animal, T
{
    usually() = default ;
    explicit usually( int s ) : T(s) {} ;
    virtual int normal_speed() const override { return T::speed() ; }
};
template < typename T > using only = usually<T> ;

struct human : usually<walks>, runs, swims { /* ... */ };
struct cheetah : usually<runs>, swims, walks { /* ... */ };
struct bluejay : usually<flies>, walks { /* ... */ };
struct trout : only<swims> { /* ... */ };

int main()
{
    human h ;
    std::cout << h.normal_speed() << ' ' << h.runs::speed() << '\n' ;

    bluejay b ;
    std::cout << b.normal_speed() << ' ' << b.walks::speed() << '\n' ;

    cheetah c ;
    trout t ;

    std::reference_wrapper< const animal > animals[] = { h, b, c, t } ;
    for( const auto& w : animals ) std::cout << w.get().normal_speed() << ' ' ;
}
