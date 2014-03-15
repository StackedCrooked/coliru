#include <iostream>
#include <vector>
#include <algorithm>

template < typename T >
int dichofind( std::vector<T> const & ref, T const & val ) {
    auto local = [&]( int beg, int end, auto & inner ) -> int {
        if ( beg == end )
            return -1;
        int mid = ( beg + end ) / 2;
        auto & midVal = ref[mid];
        if ( val < midVal )
            return inner( beg, mid, inner);
        else if ( midVal < val )
            return inner( ++mid, end, inner);
        return mid;
    };
    return local( 0, ref.size(), local);
}

int main() {
	std::vector<int> tab { 4, 6, 123, 12, 87, 13, 93, 43 };
    std::sort(begin(tab),end(tab));
        
    auto test = [&]( int v ) {
        auto idx = dichofind(tab,v);
        if (idx !=-1)
            std::cout << v << " is at idx = " << idx << "\n";
        else
            std::cout << v << " do not exist\n";
    };
    
    for( auto v : tab )
        test(v);
    
    test(5557);
    test(-5);
}