#include <cstdlib>
#include <iostream>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

//////////////////////////////////////////////////////////////////////////////////

struct Base1
{
    Base1( unsigned& val ) : m_val( val ){}
	bool operator==( const Base1& rhs )const { return m_val == rhs.m_val; }
	unsigned& m_val;
};

//////////////////////////////////////////////////////////////////////////////////

struct Base2
{
	Base2( unsigned& val ) : m_val( val ){}
	bool operator==( const Base2& rhs ) const { return m_val == rhs.m_val; }
	unsigned& m_val;
};

//////////////////////////////////////////////////////////////////////////////////

//This is the last base case
template <typename T, typename Base>
bool compare_bases(const T&lhs, const T& rhs) {
        return static_cast<const Base&>(lhs) == static_cast<const Base&>(rhs);
}


#define TYPENAME_BASE(N) BOOST_PP_ENUM_SHIFTED_PARAMS(N, typename Base)
#define EXPAND_REMAINING_BASES(N) BOOST_PP_ENUM_SHIFTED_PARAMS(N,Base)

//The following generates
//
//template <typename T, typename Base0, typename Base1>
//bool compare_bases(const T& lhs, const T& rhs);
//template <typename T, typename Base0, typename Base1, typename Base2>
//bool compare_bases(const T& lhs, const T& rhs);
//template <typename T, typename Base0, typename Base1, typename Base2, typename Base3>
//bool compare_bases(const T& lhs, const T& rhs);
//...
#define GENERATE_COMPARE_BASES_DECL(_,N,__) \
template <typename T, typename Base0, TYPENAME_BASE(N)> \
bool compare_bases(const T&lhs, const T& rhs);

BOOST_PP_REPEAT_FROM_TO(2,10,GENERATE_COMPARE_BASES_DECL,_)
#undef GENERATE_COMPARE_BASES_DECL


//The following generates
//
//template <typename T, typename Base0, typename Base1>
//bool compare_bases(const T& lhs, const T& rhs){
//    return static_cast<const Base0&>(lhs)==static_cast<const Base0&>(rhs) 
//           && compare_bases<T,Base1>(lhs,rhs);
//}
//template <typename T, typename Base0, typename Base1, typename Base2>
//bool compare_bases(const T& lhs, const T& rhs)
//    return static_cast<const Base0&>(lhs)==static_cast<const Base0&>(rhs) 
//           && compare_bases<T,Base1,Base2>(lhs,rhs);
//}
//template <typename T, typename Base0, typename Base1, typename Base2, typename Base3>
//bool compare_bases(const T& lhs, const T& rhs)
//    return static_cast<const Base0&>(lhs)==static_cast<const Base0&>(rhs) 
//           && compare_bases<T,Base1,Base2,Base3>(lhs,rhs);
//}
//...

#define GENERATE_COMPARE_BASES(_,N,__) \
template <typename T, typename Base0, TYPENAME_BASE(N)> \
bool compare_bases(const T&lhs, const T& rhs) { \
        return static_cast<const Base0&>(lhs) == static_cast<const Base0&>(rhs) \
               && compare_bases <T, EXPAND_REMAINING_BASES(N)>(lhs, rhs); \
} 

BOOST_PP_REPEAT_FROM_TO(2,10,GENERATE_COMPARE_BASES,_)
#undef TYPENAME_BASE
#undef EXPAND_REMAINING_BASES
#undef GENERATE_COMPARE_BASES



//////////////////////////////////////////////////////////////////////////////////

class Derived : public Base1 , public Base2		// Real problem has many more more Base classes
{
public:
	Derived( unsigned& val1 , unsigned& val2 ) : Base1( val1 ) , Base2( val2 )
	{
	}
	
	bool operator==( const Derived& rhs ) const	// How to generalize this 
	{
		return compare_bases<Derived, Base1, Base2>(*this, rhs);
	}
};

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	unsigned val1 = 42 , val2 = 24 , val3 = 0;
	Derived d1( val1 , val2 );
	Derived d2( val1 , val3 );
    Derived d3( val1 , val2 );

    std::cout << std::boolalpha;
	std::cout << ( d1 == d2 ) << std::endl;
    std::cout << ( d1 == d3 ) << std::endl;
	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////