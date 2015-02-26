#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>
#include <vector>

/*template <typename T>
struct xrange {
    
    
};*/

struct to_t { };
const auto to = to_t();

struct pattern_t { };
const auto pattern = pattern_t();

template <typename T>
struct set_build {
    std::vector<T> items;
    
    set_build ( std::vector<T> build ) : items(std::move(build)) {
        
    }
    
    typename std::vector<T>::iterator begin () {
        return std::begin( items );
    }
    
    typename std::vector<T>::iterator end () {
        return std::end( items );
    }
    
    typename std::vector<T>::const_iterator begin () const {
        return std::begin( items );
    }
    
    typename std::vector<T>::const_iterator end () const {
        return std::end( items );
    }
    
    template <typename TFx>
    set_build<T>& operator, ( TFx&& fx ) {
        std::vector<T> filtered;
        filtered.reserve( items.size() );
        for ( auto&& item : items ) {
            if ( fx( item ) )
                filtered.emplace_back( item );
        }
        items = std::move( filtered );
        return *this;
    }
    
};

template <typename TFx, typename T>
set_build<T> operator| ( TFx&& fx, const set_build<T>& set ) {
    std::vector<T> comprehension;
    comprehension.reserve( set.items.size() );
    for ( auto& item : set ) {
       comprehension.emplace_back( fx( item ) );
    }
    return set_build<T>( std::move( comprehension ) );
}

template <typename TFx, typename T>
set_build<T> operator| ( const set_build<T>& set, TFx&& fx ) {
    std::vector<T> comprehension;
    comprehension.reserve( set.items.size() );
    for ( auto& item : set ) {
       comprehension.emplace_back( fx( item ) );
    }
    return set_build<T>( std::move( comprehension ) );
}

template <typename T, typename T0, typename T1 = T0, typename TDiff = decltype( std::declval<T1>() - std::declval<T0>() )>
set_build<T> build_specific ( T0&& n0, const to_t&, T1&& n1, TDiff&& ndiff = static_cast<TDiff>(1) ) {
    std::vector<T> items;
    if ( n0 == n1 || ndiff == static_cast<TDiff>( 0 ) )
        return set_build<T>( std::move( items ) );
    
    T c0 = n0;
    
    if ( n0 < n1 ) {
        if ( ndiff < static_cast<TDiff>( 0 ) )
            return set_build<T>( std::move( items ) );
        
        while ( c0 != n1 ) {
            items.emplace_back( c0 );
            c0 += ndiff;
        }
    }
    else {
        if ( ndiff > static_cast<TDiff>( 0 ) )
            return set_build<T>( std::move( items ) );
        
        while ( c0 != n1 ) {
            items.emplace_back( c0 );
            c0 += ndiff;
        }
    }
    
    return set_build<T>( std::move( items ) );
}

template <typename T0, typename T1 = T0, typename TDiff = decltype( std::declval<T1>() - std::declval<T0>() )>
set_build<T0> build ( T0&& n0, const to_t& style, T1&& n1, TDiff&& ndiff = static_cast<TDiff>(1) ) {
    return build_specific<T0, T0, T1, TDiff>( std::forward<T0>( n0 ), style, std::forward<T1>( n1 ), std::forward<TDiff>( ndiff ) ); 
}

struct prelude_t {
    
    template <typename T>
    const set_build<T>& operator [] ( const set_build<T>& s ) const {
        return s;
    }
};

const auto Haskell = prelude_t();



int main ( int argc, char** argv ) {
	// While the next line would be the ideal math-like syntax
    // we can't have it because `operator|` is left-associative
    // we, instead of the below...
    //auto results = [ ( x * x ) | (1, 20) | (x * x > 144) ] ;
    
    // we start with a range instead, so we can build it up from there
    // also, in C++ we use lambdas
    //auto results = [ build(1, to, 20) | ( x * x ) | (x * x > 144) ] ;
    //auto lambda = ;
    auto results = Haskell[ 
        ( build( 1, to, 20 ), []( int x ){ return x * x > 144; } ) | []( int x ) { return x * x; } 
    ];
    
    std::cout << "[ ";
    for ( auto& result : results ) {
        std::cout << result << ' ';
    }
    std::cout << "]";
    
}