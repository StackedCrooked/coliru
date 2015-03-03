// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>
#include <typeinfo>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

#define sc_uint   static constexpr  unsigned int

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < int k, int _offset, typename... P >
struct Recursor;

template < int k, int _offset, typename _Tn, typename... P >
struct Recursor<k, _offset, _Tn, P...> 
{
public:
    // split Tn into Type[dim]
    using Tn = _Tn;
    using EltType = typename remove_extent<Tn>::type;
    
    sc_uint  dim        = extent<Tn>::value;
    sc_uint  offset     = _offset;
    sc_uint  attr_size  = sizeof(Tn);
    sc_uint  elt_size   = sizeof(EltType);

private:
    // remember at least one elt has been split off from P
    static_assert( 0 <= k  &&  k <= sizeof...(P),  "k out of bounds" ); 
    
    using This = Recursor< k  , offset          , Tn, P... >;
    using Next = Recursor< k-1, offset+attr_size,     P... >;

public:
    // usage: e.g. 
    //      using Ri = Recursor<i, 0, W>::destination;
    //      cout << Ri::offset;
    using destination = typename  conditional< k == 0, This, Next >::type;

    // bytecount counts bytes of elements k thru N, so bytecount of k=0
    // will calculate total bytes
    sc_uint  bytecount = attr_size + Next::bytecount;
    
    // MUST call this like:
    //      Recursor<N-1, 0, W>::setup_gl(0); // N = number of attributes
    static void setup_gl(int total_bytes, int attribNumber) 
    {
        //glEnableVertexAttribArray( attribNumber );

        //generic_glVertexAttribPointer< EltType >(
        //    attribNumber,
        //    dim,
        //    size,
        //    offset
        //    );
        
        cout << "k: " << k << ":" 
                << dim 
                << typeid(EltType).name() << "(" 
                << "attr_size:" << attr_size << ", " 
                << "offset: "   << offset    << ")" << endl; 
        
        
        Next::setup_gl( total_bytes, attribNumber+1 );
    }
};

template < int _offset, typename... P >
struct Recursor<-1, _offset, P...> 
{
    sc_uint  bytecount = 0;
    static void setup_gl(int, int) { cout << "done" << endl; }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template< typename... P > 
struct Attribute
{
    sc_uint  N = sizeof...(P);
    
    // Extract data for the k-th parameter in pack P
    // (Always pass an initial set of 0)
    template< int k > 
    using R = Recursor< k, 0, P... >;

    // Raw storage
    sc_uint  total_bytes = R<N-1>::bytecount;
    uint8_t data[ total_bytes ];
    
    static void setup_gl() {
        R<N-1>::setup_gl(total_bytes, 0);
    }

    template< int k >  using A       = typename R<k>::destination;
    
    template< int k >  using Tn      = typename A<k>::Tn;     // of form T[n], e.g. float[3]
    template< int k >  using EltType = typename A<k>::EltType;
    //template< int k >  using offset  = typename A<k>::offset;
    //template< int k >  using size    = typename A<k>::size;

    //sc_uint  attr_offset(sc_uint k)           { return data + offset<k>; }
    //sc_uint  elt_offset(sc_uint k, sc_uint e) { return data + offset<k> + e*sizeof(EltType<k>); }

    template <int k>
    Tn<k> get() {
        static_assert( k>=0  &&  k<N,  "Attribute index out of range!" );
        Tn<k> ret;
        memcpy( &ret,  data + A<k>::offset,  A<k>::size );
        return ret;
    }
    
    template <int k>
    void set( Tn<k>& ref ) {
        static_assert( k>=0  &&  k<N,  "Attribute index out of range!" );
        memcpy( data + A<k>::offset,  &ref,  A<k>::size );
    }
    
    template <int k, int e>
    EltType<k> get() {
        static_assert( k>=0 && k<N  &&  e>=0 && e < A<k>::dim,  "Attribute or Element index out of range!" );
        EltType<k> ret;
        memcpy( &ret,  data + A<k>::offset + e*A<k>::elt_size,  A<k>::elt_size );
        return ret;
    }
    
    template <int k, int e>
    void set( EltType<k>& ref ) {
        static_assert( k>=0 && k<N  &&  e>=0 && e < A<k>::dim,  "Attribute or Element index out of range!" );
        memcpy( data + A<k>::offset + e*A<k>::elt_size,  &ref,  A<k>::elt_size );
    } 
    
    
//    template< int index, typename... P >
//    void set_all( int index, P...p );

    template< int index, typename P0,  typename... Px >
    void set_all( P0 p0,  Px... p )
    {
        set<index>( p0 );
        set_all<index+1, p...>;
    }
    
    template< int index >
    void set_all<N>()
    { }
    
    
    Attribute( P... params ) {
        set_all<0>( params... );
    }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main()
{    
    using V = Attribute< float[3], int[1], double[4] >;
    
    COUT( sizeof(V) );
    COUT( V::total_bytes );

    V::setup_gl();
    
    V v( {1.f,2.f,3.f}, {4}, {5.,6.,7.,8.} );
    
    v.set<2>( { 50., 60. } );
    
    COUT( v.get<2>() );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
