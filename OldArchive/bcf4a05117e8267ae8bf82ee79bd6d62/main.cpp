

#if __cplusplus > 199711L
#define HAS_CXX11 
#endif


#include <cstddef>
#include <climits>
#include <iterator>

#if defined(HAS_CXX11)
#include <type_traits>
#include <array>
#else
#include <boost/type_traits.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>
#endif

#if defined(DEBUG)
#define PRINT_NAME std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
#define PRINT_NAME
#endif 

#if defined(__GNUC__) && !defined(__clang__)
    #define FORCE_INLINE __attribute__((flatten))
#else	
	#define FORCE_INLINE inline
#endif

namespace constant_time
{
	using std::iterator_traits;
#if defined(HAS_CXX11)
		using std::make_unsigned;
		using std::is_unsigned;
		using std::is_integral;
		using std::remove_reference;
		using std::common_type;
		using std::array;
		using std::true_type;
		using std::false_type;
		using std::next;
#else
		using boost::make_unsigned;
		using boost::is_unsigned;
		using boost::is_integral;
		using boost::remove_reference;
		using boost::common_type;
		using boost::array;
		using boost::true_type;
		using boost::false_type;
		using boost::next;
#endif
	namespace detail
	{
		template<typename T>
		struct bits
		{
			static const size_t value = sizeof(T) * CHAR_BIT;
		};

		template<bool B, class T = void>
		struct enable_if {};
		 
		template<class T>
		struct enable_if<true, T> { typedef T type; };

		template<size_t N>
		struct anybit_reduce
		{
			template<typename T>
			static T reduce(T const& m)
			{
				return anybit_reduce<N/2>::reduce(m | (m >> N));
			}
		};

		template<>
		struct anybit_reduce<0>
		{
			template<typename T>
			static T reduce(T const& m)
			{
				return m;
			}
		};

		// returns true iff m == 0
		template<typename T>
		typename enable_if<is_unsigned<T>::value && is_integral<T>::value, bool>::type 
		anybit(T const& m) 
		{
			return 1 ^ (1&anybit_reduce<bits<T>::value/2>::reduce(m));
		}

		template<size_t N>
		struct comparer
		{
			template<typename ValueType, typename ForwardIt1, typename ForwardIt2>
			static bool verify(const ValueType co, ForwardIt1 in1, ForwardIt2 in2) 
			{
				typedef typename make_unsigned<typename iterator_traits<ForwardIt1>::value_type>::type UCType1;
				typedef typename make_unsigned<typename iterator_traits<ForwardIt2>::value_type>::type UCType2;
				return comparer<N - 1>::verify(static_cast<ValueType>(co | (static_cast<UCType1>(*in1) ^ static_cast<UCType2>(*in2))), next(in1), next(in2));
			}
		};

		template<>
		struct comparer<1>
		{
			template<typename ValueType, typename ForwardIt1, typename ForwardIt2>
			static bool verify(const ValueType co, ForwardIt1 in1, ForwardIt2 in2)
			{
				typedef typename make_unsigned<typename iterator_traits<ForwardIt1>::value_type>::type UCType1;
				typedef typename make_unsigned<typename iterator_traits<ForwardIt2>::value_type>::type UCType2;
				return anybit( static_cast<ValueType>(co | (static_cast<UCType1>(*in1) ^ static_cast<UCType2>(*in2))) );
			}	
		};

		template<>
		struct comparer<0>
		{
			template<typename ValueType, typename ForwardIt1, typename ForwardIt2>
			static bool verify(const ValueType co, ForwardIt1 in1, ForwardIt2 in2)
			{
				return false;
			}
		};

		template<typename ForwardIt1, typename ForwardIt2>
		bool verify_runtime(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) // STL style
		{
			typedef typename make_unsigned<typename iterator_traits<ForwardIt1>::value_type>::type UCType1;
			typedef typename make_unsigned<typename iterator_traits<ForwardIt2>::value_type>::type UCType2;
			typedef typename make_unsigned<typename remove_reference<typename common_type<UCType1, UCType2>::type>::type>::type Accum;

			Accum accum(0);
			for(; first1 != last1; ++first1, ++first2)
				accum |= static_cast<UCType1>(*first1) ^ static_cast<UCType2>(*first2);
			return anybit(accum);
		}


		template<typename T, typename R = void>
		struct enable_if_type
		{
			typedef R type;
		};

		template<typename T, typename B = void>
		struct has_iterator : false_type {};

		template<typename T>
		struct has_iterator<T, typename enable_if_type<typename T::iterator>::type> : true_type {};
	}

	// Declarations where size is known at compile-time
	template<typename T1, typename T2, size_t N>
	FORCE_INLINE bool verify(T1 const (&in1)[N], T2 const (&in2)[N]) // C array specialization
	{
		typedef typename make_unsigned<typename remove_reference<typename common_type<T1, T2>::type>::type >::type Accum;
		return detail::comparer<N>::verify(Accum(0), in1, in2);	
	}

	template<typename T1, typename T2, size_t N>
	FORCE_INLINE bool verify(array<T1, N> const& in1, array<T2, N> const& in2) // std::array specialization
	{
		typedef typename make_unsigned<typename remove_reference<typename common_type<T1, T2>::type>::type >::type Accum;
		return detail::comparer<N>::verify(Accum(0), in1.begin(), in2.begin());	
	}	

	template<size_t N, typename T1, typename T2>
	FORCE_INLINE bool verify(T1 const* in1, T2 const* in2) // accepts pointers, compile-time length
	{
		typedef typename make_unsigned<typename remove_reference<typename common_type<T1, T2>::type>::type >::type Accum;
		return detail::comparer<N>::verify(Accum(0), in1, in2);	
	}

	template<size_t N, typename T1, typename T2>
	FORCE_INLINE typename detail::enable_if<detail::has_iterator<T1>::value && detail::has_iterator<T2>::value, bool>::type
	verify(T1 const& in1, T2 const& in2) // accepts containers with iterators
	{
		typedef typename make_unsigned<typename remove_reference<typename common_type<typename T1::value_type, typename T2::value_type>::type>::type >::type Accum;
		return detail::comparer<N>::verify(Accum(0), in1.begin(), in2.begin());
	}

	// Declarations where size is known at runtime only
	template<typename T1, typename T2>
	FORCE_INLINE bool verify(T1 const* in1, T2 const* in2, const size_t length)
	{
		return detail::verify_runtime(in1, in1 + length, in2);	
	}

	template<typename T1, typename T2>
	FORCE_INLINE typename detail::enable_if<detail::has_iterator<T1>::value && detail::has_iterator<T2>::value, bool>::type 
	verify(T1 const& in1, T2 const& in2) // accepts containers with iterators
	{
		return std::distance(in1.begin(), in1.end()) != std::distance(in2.begin(), in2.end()) ? false
			 : detail::verify_runtime(in1.begin(), in1.end(), in2.begin());
	}
	
}


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>

int main(int argc, char **argv)
{
	using namespace std;
#if !defined(HAS_CXX11)
	using namespace boost;
#endif
	const char in1[16] = "aaaaaaaaaaaaaaa";
	const char in2[16] = "aaaaaaaaaaaaaaa";

	const char *ptr1 = in1;
	const char *ptr2 = in2;

	array<unsigned char, 16> arr1;
	array<unsigned char, 16> arr2;

	copy(in1, in1 + 16, arr1.begin());
	copy(in2, in2 + 16, arr2.begin());

	const string str1(in1, in1 + 16);
	const string str2(in2, in2 + 16);

	const vector<unsigned char> vec1(in1, in1 + 16);
	const vector<unsigned char> vec2(in2, in2 + 16);

	const list<unsigned char> lst1(in1, in1 + 16);
	const list<unsigned char> lst2(in2, in2 + 16);

	// Compile-time tests
	cout << boolalpha << constant_time::verify(in1, in2) << endl; // Array, detect size
	cout << boolalpha << constant_time::verify<16>(ptr1, ptr2) << endl; // Pointer, explicit size
	cout << boolalpha << constant_time::verify(arr1, arr2) << endl; // array<T, N>, detect size
	cout << boolalpha << constant_time::verify<16>(str1, str2) << endl; //  container, explicit size
	cout << boolalpha << constant_time::verify<16>(vec1, vec2) << endl; //  container, explicit size
	cout << boolalpha << constant_time::verify<16>(lst1, lst2) << endl; //  container, explicit size

	// Runtime tests
	cout << boolalpha << constant_time::verify(ptr1, ptr2, 16) << endl; // Pointer, explicit runtime size
	cout << boolalpha << constant_time::verify(str1, str2) << endl; //  container
	cout << boolalpha << constant_time::verify(vec1, vec2) << endl; //  container
	cout << boolalpha << constant_time::verify(lst1, lst2) << endl; //  container

	// cout << boolalpha << constant_time::verify(ptr1, ptr1 + 16, ptr2) << endl; // Pointer, iterator-style
	// cout << boolalpha << constant_time::verify(begin(lst1), end(lst1), begin(lst2)) << endl; //  iterator
	
	return 0;
}


