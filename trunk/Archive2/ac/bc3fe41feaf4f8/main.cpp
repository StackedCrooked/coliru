#include <iostream>
#include <iomanip>
#include <cstdlib>

inline int smaller_of( int a, int b ) { return a<b ? a : b ; }

class VectorFloat
{
public:

    VectorFloat() //creates an empty array of size 0
	   : m_p(nullptr), m_dim(0) {}

	VectorFloat(int n)  //create an array of given size
       : m_p( new float[n]{} ), m_dim(n) {}

	VectorFloat( const VectorFloat &vec )  //copy constructor; deep copy
	   : m_p( new float[vec.m_dim] ), m_dim(vec.m_dim)
	   { for( int i = 0 ; i < m_dim ; ++i ) m_p[i] = vec.m_p[i] ; }

	~VectorFloat() noexcept //destructor
	{ delete[] m_p ; }

	VectorFloat& operator = ( VectorFloat &vec ) // copy assignment; deep copy
	{
	    if( &vec != this ) // guard against self-assignment
        {
            // if( m_dim < vec.m_dim ) // resize (if required)
            {
                delete[] m_p ;
                m_p = new float[ vec.m_dim ] ;
            }
            m_dim = vec.m_dim ;
            for( int i = 0 ; i < m_dim ; ++i ) m_p[i] = vec.m_p[i] ;
        }
        return *this ;
	}

	// note: move construtor amd move assignment are implicitly deleted

	int size() const { return m_dim; }  //returns size of vector

	float& operator[] (int i) { quit_if_bad_index(i) ; return m_p[i] ; }
	const float& operator[] (int i) const { quit_if_bad_index(i) ; return m_p[i] ; }

	VectorFloat& operator += ( const VectorFloat &vec )
	{
	    for( int i = 0 ; i < smaller_of(m_dim,vec.m_dim) ; ++i )
	        m_p[i] += vec.m_p[i] ;
	    return *this ;
	}

	VectorFloat& operator *= ( const VectorFloat &vec )
	{
	    for( int i = 0 ; i < smaller_of(m_dim,vec.m_dim ) ; ++i )
	        m_p[i] *= vec.m_p[i] ;
	    return *this ;
	}

private:

	float *m_p;  //dynamically allocated array of objects; the vector itself
	int m_dim;  //the size of the object

	void quit_if_bad_index( int i ) const // exit if index is invalid
	{
	    if( i < 0 || i >= m_dim )
        {
            std::cerr << "VectorFloat index is out of range!" ;
            std::exit(1) ;
        }
	}
};

// prefer non-friend, non-member
VectorFloat operator + ( VectorFloat first, const VectorFloat& second )
{ return first += second ; } // note: first is passed by value

VectorFloat operator * ( VectorFloat first, const VectorFloat& second )
{ return first *= second ; } // note: first is passed by value

std::ostream& operator<< ( std::ostream& stm, const VectorFloat& seq )
{
    stm << " [" << std::fixed << std::showpoint << std::setprecision(2) ;
    for( int i = 0 ; i < seq.size() ; ++i ) stm << std::setw(6) << seq[i] << ' ' ;
    return stm << "] " ;
}

int main()
{
     VectorFloat a(6) ;
     { int i = 0 ; for( int v : { 1, 2, 3, 4, 5, 6 } ) a[i++] = v ; }
     std::cout << "a: " << a << '\n' ;

     VectorFloat b(4) ;
     { int i = 0 ; for( int v : { 7, 8, 9, 10 } ) b[i++] = v ; }
     std::cout << "b: " << b << '\n' ;

     const auto c = a + b ; // operator+ => copy constructor, operator +=
     std::cout << "c: " << c << '\n' ;

     const auto d = a * c ;
     std::cout << "d: " << d << '\n' ;

     const auto e = d ; // copy assignment
     std::cout << "e: " << e << '\n' ;
}
