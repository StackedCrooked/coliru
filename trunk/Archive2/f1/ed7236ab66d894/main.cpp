// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>

#define COUT(x) cout << #x << ":" << x << endl

using namespace std;

// * * *  AttributeRecursor  * * *

// Fills out TheStruct for k'th attribute of P...
// Use like this:
//      AttributeRecursor<k, 0, P...>::TheStruct
// (always start with bytecount = 0)

template < int k, int bytecount_in, typename ...P >
struct AttributeRecursor;

template < int k, int bytecount_in, typename Tn, typename ...P >
struct AttributeRecursor<k, bytecount_in, Tn, P...> 
{
private:
    static_assert( 0 <= k  &&  k <= sizeof...(P)-1,  "k out of bounds" );
    
    //using This = AttributeRecursor< k  , bytecount_in           , Tn, P... >;
    using Next = conditional< k == 0, void, 
                                        AttributeRecursor< k-1, bytecount_in+sizeof(Tn)    , P... >
                            >;
    
    struct TheStruct 
    {
    private:
        //using This = AttributeRecursor< k  , bytecount           , Tn, P... >;
        //using Rem  = AttributeRecursor< k+1, bytecount+sizeof(Tn),     P... >;

    public:
        // split Tn into T[dim]
        using Type = typename remove_extent<Tn>::type;
        static constexpr  unsigned int  dim = extent<Tn>::value;

        static constexpr  unsigned int  offset      = bytecount_in;
        static constexpr  unsigned int  size_bytes  = sizeof(Tn);
        static constexpr  unsigned int  total_bytes = bytecount_in+sizeof(Tn);

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

            Next::TheStruct::setup();
         }
    }; // TheStruct

public:    
    using type = conditional< 
                        k == 0, 
                        TheStruct, 
                        typename Next::TheStruct
                        >;
};

// recursion terminator
template<int attribute_index, int bytecount>
struct AttributeRecursor <-1, bytecount> {
    struct TheStruct {
        static void setup(){}
    };
    using type = void;
    //static constexpr  unsigned int  offset = bytecount;
    //static void setup() { cout << "terminator" << endl; };
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
    using A = typename AttributeRecursor< k, 0, P... >::type;

    // A's range is 0 to N-1; N is the recursion terminator
    static constexpr  unsigned int  total_bytes = A<N-1>::total_bytes;

    unsigned char data[ total_bytes ];

public:
    template <int k>
    typename A<k>::Type get() {
        static_assert( k>=0  &&  k<N,  "Element is out of range!" );
        typename A<k>::Type ret;
        memcpy(
                    &ret,
                    data + A<k>::offset,
                    A<k>::size_bytes
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
                    A<k>::size_bytes
                    );
    }
    
    static void setup()
    {
        A<N-1>::setup();
    }
};


int main()
{    
    using V = AttributeHandler< float[1] >; // , int[2], double[4] >;
    
    COUT( sizeof(V) );
    
    //V::setup();
}