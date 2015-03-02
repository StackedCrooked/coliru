// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>
#include <typeinfo>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

// * * *  AttributeRecursor  * * *

// Fills out for k'th attribute of P...
// Use like this:
//      AttributeRecursor<k, 0, P...>::recursor
// (always start with bytecount = 0)

template < int k, int bytecount_in, typename ...P >
struct AttributeRecursor;

template < int k, int bytecount_in, typename Tn, typename ...P >
struct AttributeRecursor<k, bytecount_in, Tn, P...> 
{
private:
    static_assert( 0 <= k  &&  k <= sizeof...(P),  "k out of bounds" );
    
    using This = AttributeRecursor< k  , bytecount_in           , Tn, P... >;
    using Next = AttributeRecursor< k-1, bytecount_in+sizeof(Tn),     P... >;

public:    
    using destination = typename  conditional< k == 0, This, Next >::type;

public:
    // split Tn into Type[dim]
    using Type = typename remove_extent<Tn>::type;
    static constexpr  unsigned int  dim = extent<Tn>::value;

    //static constexpr  unsigned int  offset      = bytecount_in;
    static constexpr  unsigned int  size_bytes  = sizeof(Tn);
    //static constexpr  unsigned int  total_bytes = bytecount_in+sizeof(Tn);

    static constexpr  unsigned int  remaining_bytes = size_bytes + Next::remaining_bytes;

    static void setup()
    {
        //glEnableVertexAttribArray( k );

        //generic_glVertexAttribPointer< Type >(
        //    k,
        //    dim,
        //    size_bytes,
        //    byteoffset
        //    );

        cout << "\n" << typeid(Type).name() << endl;
        COUT( typeid(Type).name() );
        COUT( dim ); 
        COUT( size_bytes );
        COUT( remaining_bytes ); 

        Next::setup();
     }

};

// recursion terminator
template< int bytecount_in, typename ...P >
struct AttributeRecursor <-1, bytecount_in, P...> 
{
    //static constexpr  unsigned int  total_bytes = bytecount_in;
    static constexpr  unsigned int  remaining_bytes = 0;

    //using This = AttributeRecursor< -1  , /*bytecount_in,*/ P... >;
    //using type = This;

    static void setup() { cout << "terminator" << endl; };
};

// * * *  AttributeHandler  * * *

template < typename... P >
struct AttributeHandler
{
private:
    // Number of attributes
    static constexpr  unsigned int  N = sizeof...(P);
    
    // A<k> is the k'th attribute
    //    allow e.g. `cout << A<2>::size_bytes;`
    template <int k>
    using AR = typename AttributeRecursor< k, 0, P... >;
    
    // A<k> is the k'th attribute
    //    allow e.g. `cout << A<2>::size_bytes;`
    template <int k>
    using D = typename AR<k>::destination;

    
    // A's range is 0 to N-1; N hits the recursion terminator
    static constexpr  unsigned int  total_bytes = AR<0>::remaining_bytes;

    unsigned char data[ total_bytes ];

public:
    template <int k>
    typename D<k>::Type get() {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename D<k>::Type ret;
        memcpy(
                    &ret,
                    data + total_bytes-D<k>::remaining_bytes /*A<k>::offset*/,
                    D<k>::size_bytes
                    );
        return ret;
    }
    
    template <int k>
    void set( typename R<k>::Type& ref ) {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename D<k>::Type ret;
        memcpy(
                    data + D<k>::offset,
                    &ret,
                    D<k>::size_bytes
                    );
    }
    
    static void setup()
    {
        AR<N-1>::setup();
    }
};


int main()
{    
    //using V = AttributeHandler< float[3], int[1], double[4] >;
    using V = AttributeHandler< int[1], int[1] >;
    
    COUT( sizeof(V) );
    
    V::setup();
}