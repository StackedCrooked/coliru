// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

// * * *  AttributeRecursor  * * *

template < int k, int bytecount, typename ...P >
struct AttributeRecursor;

template < int k, int bytecount, typename Tn, typename ...P >
struct AttributeRecursor<k, bytecount, Tn, P...> 
{
private:
    using This = AttributeRecursor< k  , bytecount           , Tn, P... >;
    using Rem  = AttributeRecursor< k+1, bytecount+sizeof(Tn),     P... >;

public:
    // split Tn into T[dim]
    using Type = typename remove_extent<Tn>::type;
    static constexpr  unsigned int  dim = extent<Tn>::value;
    
    static constexpr  unsigned int  offset = bytecount;
    static constexpr  unsigned int  size_bytes = sizeof(Tn);
    
    static void setup()
    {
        //glEnableVertexAttribArray( k );

        //generic_glVertexAttribPointer< Type >(
        //    k,
        //    dim,
        //    size_bytes,
        //    byteoffset
        //    );

        cout << "Attr[" << k << "]" << endl;
        COUT( dim ); 
        COUT( size_bytes );
        COUT( offset ); 
        
        Rem::setup();
     }
};

// recursion terminator
template<int attribute_index, int bytecount>
struct AttributeRecursor <attribute_index, bytecount> {
    static constexpr  unsigned int  offset = bytecount;
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
    using A = typename AttributeRecursor< k, 0, P... >;

    // A's range is 0 to N-1; N is the recursion terminator
    static constexpr  unsigned int  total_bytes = A<N>::offset;

    unsigned char data[ total_bytes ];

public:
    template <int k>
    A<k>::Type get() {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        A<k>::Type ret;
        std::memcpy(
                    &ret,
                    data + A<k>::offset,
                    A<k>::size_bytes
                    );
        return ret;
    }
    
    template <int k>
    void set( A<k>::Type& ref ) {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        A<k>::Type ret;
        std::memcpy(
                    data + A<k>::offset,
                    &ret,
                    A<k>::size_bytes
                    );
    }
};


int main()
{    
    using V = AttributeHandler< float[3], int[2], double[4] >;
    COUT( sizeof(V) );
    
    V::setup();
}