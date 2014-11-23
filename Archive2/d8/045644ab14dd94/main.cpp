#include <iostream>
#include <functional>
#include <vector>
#include <typeinfo>

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

struct animal
{
    virtual ~animal() = default ;
    virtual int normal_speed() const = 0 ;
    virtual std::vector<int> all_speeds() const { return {} ; }
    virtual std::ostream& save_speeds( std::ostream& stm ) const
    { for( int s : all_speeds() ) stm << s << ' ' ; return stm ; }
};

template < typename T > struct usually : virtual animal, T
{
    usually() = default ;
    explicit usually( int s ) : T(s) {} ;
    virtual int normal_speed() const override { return T::speed() ; }
    virtual std::vector<int> all_speeds() const override { return { T::speed() } ; }
};
template < typename T > using only = usually<T> ;

template < typename... > struct speeds ;
template < typename T > struct speeds<T> : T
{
    virtual std::vector<int> all_speeds() const { return { T::speed() } ; }
};

template < typename FIRST, typename... REST > struct speeds<FIRST,REST...> : speeds<FIRST>, speeds<REST...>
{
    virtual std::vector<int> all_speeds() const override
    {
        auto a = speeds<FIRST>::all_speeds() ;
        auto b = speeds<REST...>::all_speeds() ;
        a.insert( a.end(), b.begin(), b.end() ) ;
        return a ;
    }
};

struct human : speeds< usually<walks>, runs, swims > { /* ... */ };
struct cheetah : speeds< swims, usually<runs>, walks > { /* ... */ };
struct bluejay : speeds< usually<flies>, walks > { /* ... */ };
struct trout : speeds< only<swims> > { /* ... */ };

int main()
{
    human h ; std::cout << h.normal_speed() << ' ' << h.runs::speed() << '\n' ;
    bluejay b ; std::cout << b.normal_speed() << ' ' << b.walks::speed() << '\n' ;
    cheetah c ;
    trout t ;

    std::reference_wrapper< const animal > animals[] = { h, b, c, t } ;
    for( const auto& w : animals )
    {
        const animal& a = w ;
        a.save_speeds( std::cout << typeid(a).name()+1 << " speeds: " ) ; // +1: GNU specific
        std::cout << " (usually " << a.normal_speed() << ")\n" ;
    }
}
