#include <iostream>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <algorithm>

struct moves
{
    explicit constexpr moves( int s ) : speed_(s) {}
    int speed_ = 0 ;
    constexpr int speed() const { return speed_ ; }
    void speed( int v ) { speed_  = v ; }
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
    virtual void all_speeds( std::vector<int> ) {}

    virtual std::ostream& save_speeds( std::ostream& stm ) const
    { for( int s : all_speeds() ) stm << s << ' ' ; return stm << '\n' ; }

    virtual bool load_speeds( std::string str )
    {
        std::istringstream stm(str) ;
        std::vector<int> s ;
        int v ;
        while( stm >> v ) s.push_back(v) ;
        all_speeds(s) ;
        return bool(stm) ;
    }

    virtual std::istream& load_speeds( std::istream& stm )
    {
        std::string line ;
        if( std::getline( stm, line ) && load_speeds(line) ) return stm ;
        stm.setstate( std::ios::failbit ) ;
        return stm ;
    }

    template < typename FN > void adjust_speeds( FN&& fn )
    {
        auto s = all_speeds() ;
        for( int& v : s ) v = std::forward<FN>(fn)(v) ;
        all_speeds(s) ;
    }
};

template < typename T > struct usually : virtual animal, T
{
    usually() = default ;
    explicit usually( int s ) : T(s) {} ;
    virtual int normal_speed() const override { return T::speed() ; }
    virtual std::vector<int> all_speeds() const override { return { T::speed() } ; }
    virtual void all_speeds( std::vector<int> s ) override  { if( !s.empty() ) T::speed( s.front() ) ; }
};
template < typename T > using only = usually<T> ;

template < typename... > struct speeds ;
template < typename T > struct speeds<T> : T
{
    virtual std::vector<int> all_speeds() const { return { T::speed() } ; }
    virtual void all_speeds( std::vector<int> s ) { if( !s.empty() ) T::speed( s.back() ) ; }
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

    virtual void all_speeds( std::vector<int> s ) override
    {
        if( !s.empty() )
        {
            speeds<FIRST>::speed( s.front() ) ;
            speeds<REST...>::all_speeds( { s.begin() + 1, s.end() } ) ;
        }
    }
};

struct human : speeds< usually<walks>, runs, swims > { /* ... */ };
struct cheetah : speeds< swims, usually<runs>, walks > { /* ... */ };
struct bluejay : speeds< usually<flies>, walks > { /* ... */ };
struct trout : speeds< only<swims> > { /* ... */ };

int main()
{
    human h ;
    animal& a = h ;
    std::cout << "normal speed: " << a.normal_speed() << '\n' ;

    a.save_speeds( std::cout << "original speeds: " ) ;

    a.load_speeds(std::cin) ;
    a.save_speeds( std::cout << "after load_speeds: " ) ;

    a.adjust_speeds( []( int v ) { return std::max( 2*v*v - 3*v + 5, 1 ) ; } ) ;
    a.save_speeds( std::cout << "after adjust_speeds: " ) ;

}
