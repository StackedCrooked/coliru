#include <iterator>

template <typename TCont1, typename TCont2>
bool subsequence_equals( TCont1&& cont1, TCont2&& cont2 ) {
	subsequence_equals( std::begin( cont1 ), std::end( cont1 ), std::begin( cont2 ), std::end( cont2 ) );
}

template <typename TIter1, typename TIter2>
bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2 ) {
	typedef decltype( *biter1 ) ref1_t;
	typedef decltype( *biter2 ) ref2_t;
	subsequence_equals( biter1, eiter1, biter2, eiter2, [ ] ( ref1_t& a, ref2_t& b ) { return a == b; } )
}

template <typename TIter1, typename TIter2, typename TPred>
bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2, TPred predicate ) {
	T iter1 = biter1;
	T iter2 = biter2;
	while ( iter1 != eiter1 && iter2 != eiter2 ) {
		if ( !predicate( *iter1, *iter2 ) ) {
			return false;
		}
		++iter1;
		++iter2;
	}
	return true;
}

#include <iostream>
    
int main () {
    std::vector<int> a = { 1, 2, 3, 4, 5 };
    std::vector<int> b = { 1, 2, 3, 4, 5 };
    std::vector<int> c = { 1, 2, 3, 4 };
    std::cout << subsequence_equals( a, b ) << '\n';
    std::cout << subsequence_equals( a, c );
}