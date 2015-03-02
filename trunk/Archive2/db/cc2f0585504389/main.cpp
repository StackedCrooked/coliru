// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>
#include <typeinfo>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < int k, int _offset, typename ...P >
struct Recursor;

template < int k, int _offset, typename _Tn, typename ...P >
struct Recursor<k, _offset, _Tn, P...> 
{
public:
    // split Tn into Type[dim]
    using Tn = _Tn;
    using Type = typename remove_extent<Tn>::type;
    
    static constexpr  unsigned int  dim     = extent<Tn>::value;
    static constexpr  unsigned int  offset  = _offset;
    static constexpr  unsigned int  size    = sizeof(Tn);

private:
    // remember at least one elt has been split off from P
    static_assert( 0 <= k  &&  k <= sizeof...(P),  "k out of bounds" ); 
    
    using This = Recursor< k  , offset     , Tn, P... >;
    using Next = Recursor< k-1, offset+size,     P... >;

public:
    // usage: e.g. 
    //      using Ri = Recursor<i, 0, W>::destination;
    //      cout << Ri::offset;
    using destination = typename  conditional< k == 0, This, Next >::type;

    // bytecount counts bytes of elements k thru N, so bytecount of k=0
    // will calculate total bytes
    static constexpr  unsigned int  bytecount = size + Next::bytecount;
    
    // MUST call this like:
    //      Recursor<N-1, 0, W>::setup_gl(0); // N = number of attributes
    static void setup_gl(int total_bytes, int attribNumber) 
    {
        //glEnableVertexAttribArray( attribNumber );

        //generic_glVertexAttribPointer< Type >(
        //    attribNumber,
        //    dim,
        //    size,
        //    offset
        //    );
        
        cout << "k: " << k << ":" 
                << dim 
                << typeid(Type).name() << "(" 
                << "size:" << size << ", " 
                << "offset: " << offset << ")" << endl; 
        
        
        Next::setup_gl( total_bytes, attribNumber+1 );
    }
};

template < int _offset, typename ...P >
struct Recursor<-1, _offset, P...> 
{
    static constexpr  unsigned int  bytecount = 0;
    static void setup_gl(int, int) { cout << "done" << endl; }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template< typename ...P > 
struct Attribute
{
    static constexpr  unsigned int  N = sizeof...(P);
    
    // Extract data for the k-th parameter in pack P
    // (Always pass an initial set of 0)
    template< int k > 
    using R = Recursor< k, 0, P... >;

    // Raw storage
    static constexpr  unsigned int  total_bytes = R<N-1>::bytecount;
    uint8_t data[ total_bytes ];
    
    static void setup_gl() {
        R<N-1>::setup_gl(total_bytes, 0);
    }

    template< int k > 
    using A = typename R<k>::destination;
    
    template <int k>
    typename A<k>::Tn get() {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename A<k>::Tn ret;
        memcpy(
                &ret,
                data  +  total_bytes - A<k>::offset /*A<k>::offset*/,
                A<k>::size
                );
        return ret;
    }
    
    template <int k>
    void set( typename A<k>::Type& ref ) {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename A<k>::Type ret;
        memcpy(
                data + A<k>::offset,
                &ret,
                A<k>::size
                );
    }
    
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main()
{    
    using V = Attribute< float[3], int[1], double[4] >;
    
    COUT( sizeof(V) );
    COUT( V::total_bytes );

    V::setup_gl();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
