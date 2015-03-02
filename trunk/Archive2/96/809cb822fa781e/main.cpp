// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>
#include <typeinfo>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

//template< int i, typename... P >
//struct Offset;
//
//template< int i, typename P0, typename... P >
//struct Offset;
//{
//    static constexpr  unsigned int  offset = sizeof(P0) + conditional< i==0, 


// * * *  AttributeRecursor  * * *

// Fills out for k'th attribute of P...
// Use like this:
//      AttributeRecursor<k, 0, P...>::recursor
// (always start with bytecount = 0)

template < int k, typename ...P >
struct AttributeRecursor;

template < int k, typename Tn, typename ...P >
struct AttributeRecursor<k, Tn, P...> 
{
private:
    static_assert( 0 <= k  &&  k <= sizeof...(P),  "k out of bounds" );
    
    using This = AttributeRecursor< k  , Tn, P... >;
    using Next = AttributeRecursor< k-1,     P... >;

public:    
    using destination = typename  conditional< k == 0, This, Next >::type;

public:
    // split Tn into Type[dim]
    using Type = typename remove_extent<Tn>::type;
    static constexpr  unsigned int  dim = extent<Tn>::value;

    static constexpr  unsigned int  offset      = Next::bytes_from_P0; // bytecount_in;
    static constexpr  unsigned int  size_bytes  = sizeof(Tn);
    //static constexpr  unsigned int  total_bytes = bytecount_in+sizeof(Tn);

    static constexpr  unsigned int  bytes_from_P0 = size_bytes + Next::bytes_from_P0; // + Next::remaining_bytes;

    static void setup()
    {
        //glEnableVertexAttribArray( k );

        //generic_glVertexAttribPointer< Type >(
        //    k,
        //    dim,
        //    size_bytes,
        //    byteoffset
        //    );

        cout << endl;
        COUT( k );
        cout << "Type:" << typeid(Type).name() << endl;
        COUT( dim ); 
        COUT( size_bytes );
        COUT( offset ); 
        COUT( bytes_from_P0 ); 

        Next::setup();
     }

};

// recursion terminator
template< typename ...P >
struct AttributeRecursor <-1, P...> 
{
    //static constexpr  unsigned int  total_bytes = bytecount_in;
    static constexpr  unsigned int  bytes_from_P0 = 0;

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
    using AR = AttributeRecursor< k, P... >;
    
    // A<k> is the k'th attribute
    //    allow e.g. `cout << A<2>::size_bytes;`
    template <int k>
    using D = typename AR<k>::destination;

    
    // A's range is 0 to N-1; N hits the recursion terminator
    static constexpr  unsigned int  total_bytes = AR<N-1>::bytes_from_P0;

    unsigned char data[ total_bytes ];

public:
    template <int k>
    typename D<k>::Type get() {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename D<k>::Type ret;
        memcpy(
                    &ret,
                    data  +  total_bytes - D<k>::offset /*A<k>::offset*/,
                    D<k>::size_bytes
                    );
        return ret;
    }
    
    template <int k>
    void set( typename D<k>::Type& ref ) {
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
    using V = AttributeHandler< int[1], int[2], int[3] >;
    
    COUT( sizeof(V) );
    
    V::setup();
}