#include </Archive2/c0/b81106f10ba269/main.cpp>
#include <type_traits>

    template<typename T>
	struct unqualified {
		typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
	};

	template <typename T>
	using unqualified_t = typename unqualified<T>::type;

#include <functional>

    struct left_smaller_t { };
	const auto left_smaller = left_smaller_t{ };

	struct right_smaller_t { };
	const auto right_smaller = right_smaller_t{ };

	template <typename T>
	struct range_capacity_compare {
		bool operator()( left_smaller_t ) const {
			return false;
		}

		bool operator()( right_smaller_t ) const {
			return false;
		}
	};

	template <typename T>
	struct range_capacity_compare<std::less<T>> {
		bool operator()( left_smaller_t ) const {
			return true;
		}

		bool operator()( right_smaller_t ) const {
			return false;
		}
	};

    template <typename It1, typename It2, typename Pred, typename RangeCapacityCompare = range_capacity_compare<Pred>>
	bool compare( It1 first1, It1 last1, It2 first2, It2 last2, Pred&& pred, RangeCapacityCompare&& capacitypred ) {
		while ( true ) {
			bool it1done = first1 == last1;
			bool it2done = first2 == last2;
			if ( it1done && it2done )
				break;
			if ( it1done )
				return capacitypred( left_smaller );
			if ( it2done )
				return capacitypred( right_smaller );
			if ( !pred( *first1++, *first2++ ) )
				return false;
		}
		return true;
	}

    template <typename It1, typename It2, typename Pred>
    bool compare( It1 first1, It1 last1, It2 first2, It2 last2, Pred&& pred ) {
        typedef range_capacity_compare<typename unqualified<Pred>::type> rcc_t;
        return compare( std::move( first1 ), std::move( first1 ), std::move( first1 ), std::move( first1 ), std::forward<Pred>( pred ), rcc_t() );
    }

    template <typename Range1, typename Range2, typename Pred, typename RangeCapacityCompare>
	bool compare( Range1&& range1, Range2&& range2, Pred&& pred, RangeCapacityCompare&& capacitypred ) {
		using std::begin;
		using std::end;
		return compare( begin( range1 ), end( range1 ), begin( range2 ), end( range2 ), std::forward<Pred>( pred ), std::forward<RangeCapacityCompare>( capacitypred ) );
	}

    template <typename Range1, typename Range2, typename Pred>
    bool compare( Range1&& range1, Range2&& range2, Pred&& pred ) {
		typedef range_capacity_compare<typename unqualified<Pred>::type> rcc_t;
		return compare( std::forward<Range1>( range1 ), std::forward<Range2>( range2 ), std::forward<Pred>( pred ), rcc_t( ) );
	}

#include <string>
#include <iostream>

int main () {
   
   std::string s = "Woof", r = "Woof";
   
   std::cout << std::boolalpha;
   std::cout << compare( s, r, std::equal_to<void>() ) << std::endl;
   
}