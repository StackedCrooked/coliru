// https://github.com/julianstorer/JUCE/blob/master/examples/Demo/Source/Demos/OpenGLDemo.cpp#L51

#include <string>
#include <iostream>
#include <typeinfo>
#include <cstring> // memcpy (!)
#include <array>

#define COUT(x) cout << #x << ":  " << x << endl

#define XCOUT(x) cout << #x << endl; x

using namespace std;

#define sc_uint   static constexpr  unsigned int

// from gltypes.h
typedef uint32_t GLbitfield;
typedef uint8_t  GLboolean;
typedef int8_t   GLbyte;
typedef float    GLclampf;
typedef uint32_t GLenum;
typedef float    GLfloat;
typedef int32_t  GLint;
typedef int16_t  GLshort;
typedef int32_t  GLsizei;
typedef uint8_t  GLubyte;
typedef uint32_t GLuint;
typedef uint16_t GLushort;
typedef void     GLvoid;

// from gl3.h
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A

#define GL_FALSE                          0
#define GL_TRUE                           1

#define GLAPI
#define APIENTRY

GLAPI void APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexAttribLPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template <typename T>
struct glconst4type
{
    static_assert( std::is_same<T, void>::value,  "Invalid type!" );
    static constexpr GLenum value = 0;
};

template <> struct glconst4type<unsigned char>  {static constexpr GLenum value = GL_UNSIGNED_BYTE;};
template <> struct glconst4type<signed char>    {static constexpr GLenum value = GL_BYTE;};
//template <> struct glconst4type<char>           {static constexpr GLenum value = Utils::is_char_signed ? GL_BYTE : GL_UNSIGNED_BYTE;};
template <> struct glconst4type<unsigned short> {static constexpr GLenum value = GL_UNSIGNED_SHORT;};
template <> struct glconst4type<signed short>   {static constexpr GLenum value = GL_SHORT;};
template <> struct glconst4type<unsigned int>   {static constexpr GLenum value = GL_UNSIGNED_INT;};
template <> struct glconst4type<signed int>     {static constexpr GLenum value = GL_INT;};
template <> struct glconst4type<float>          {static constexpr GLenum value = GL_FLOAT;};
template <> struct glconst4type<double>         {static constexpr GLenum value = GL_DOUBLE;};


template <typename T>
inline void generic_glVertexAttribPointer(GLuint index, GLint size, GLsizei stride, const GLvoid *pointer) {
    static_assert( glconst4type<T>::value,  "Invalid type!" );
    glVertexAttribIPointer( index, size, glconst4type<T>::value,                 stride, pointer );
}

template <>
inline void generic_glVertexAttribPointer<float>(GLuint index, GLint size, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribPointer( index, size, glconst4type<float>::value, GL_FALSE,    stride, pointer );
}

template <>
inline void generic_glVertexAttribPointer<double>(GLuint index, GLint size, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribLPointer( index, size, glconst4type<double>::value,            stride, pointer );
}


template <typename T, unsigned int D>
struct Vec {
    static_assert( (std::is_void<T>::value || glconst4type<T>::value)  &&  D <= 4,  "Invalid dimension for vector!" );
    static constexpr int dim = 0;
    using type = void;
};


template <typename T>
struct Vec<T, 1> {
    using type = T;
    static constexpr int dim = 1;
    T x;
    Vec<T, 1>  operator- ()                   const {return {-x};}
    Vec<T, 1>  operator+ (const Vec<T, 1> &o) const {return {x + o.x};}
    Vec<T, 1>  operator- (const Vec<T, 1> &o) const {return {x - o.x};}
    Vec<T, 1> &operator+=(const Vec<T, 1> &o)       {x += o.x; return *this;}
    Vec<T, 1> &operator-=(const Vec<T, 1> &o)       {x -= o.x; return *this;}
};

template <typename T>
struct Vec<T, 2> {
    using type = T;
    static constexpr int dim = 2;
    union {T x, u;};
    union {T y, v;};
    Vec<T, 2>  operator- ()                   const {return {-x, -y};}
    Vec<T, 2>  operator+ (const Vec<T, 2> &o) const {return {x + o.x, y + o.y};}
    Vec<T, 2>  operator- (const Vec<T, 2> &o) const {return {x - o.x, y - o.y};}
    Vec<T, 2> &operator+=(const Vec<T, 2> &o)       {x += o.x; y += o.y; return *this;}
    Vec<T, 2> &operator-=(const Vec<T, 2> &o)       {x -= o.x; y -= o.y; return *this;}
};

template <typename T>
struct Vec<T, 3> {
    using type = T;
    static constexpr int dim = 3;
    union {T x, r;};
    union {T y, g;};
    union {T z, b;};
    Vec<T, 3>  operator- ()                   const {return {-x, -y, -z};}
    Vec<T, 3>  operator+ (const Vec<T, 3> &o) const {return {x + o.x, y + o.y, z + o.z};}
    Vec<T, 3>  operator- (const Vec<T, 3> &o) const {return {x - o.x, y - o.y, z - o.z};}
    Vec<T, 3>  operator* (const Vec<T, 3> &o) const {return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x};}
    Vec<T, 3> &operator+=(const Vec<T, 3> &o)       {x += o.x; y += o.y; z += o.z; return *this;}
    Vec<T, 3> &operator-=(const Vec<T, 3> &o)       {x -= o.x; y -= o.y; z -= o.z; return *this;}
    Vec<T, 3> &operator*=(const Vec<T, 3> &o)       {*this = *this * o; return *this;}
};

template <typename T>
struct Vec<T, 4> {
    using type = T;
    static constexpr int dim = 4;
    union {T x, r;};
    union {T y, g;};
    union {T z, b;};
    union {T w, a;};
    Vec<T, 4>  operator- ()                   const {return {-x, -y, -z, -w};}
    Vec<T, 4>  operator+ (const Vec<T, 4> &o) const {return {x + o.x, y + o.y, z + o.z, w + o.w};}
    Vec<T, 4>  operator- (const Vec<T, 4> &o) const {return {x - o.x, y - o.y, z - o.z, w - o.w};}
    Vec<T, 4> &operator+=(const Vec<T, 4> &o)       {x += o.x; y += o.y; z += o.z; w += o.w; return *this;}
    Vec<T, 4> &operator-=(const Vec<T, 4> &o)       {x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this;}
};


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

template < int k, int offset_, typename... P >
struct Recursor;

template < int k, int offset_, typename Tn_, typename... P >
struct Recursor<k, offset_, Tn_, P...> 
{
public:
    // split Tn into Type[dim]
    using Tn = Tn_;
    using EltType = typename remove_extent<Tn>::type;
    
    sc_uint  dim        = extent<Tn>::value;
    sc_uint  offset     = offset_;
    sc_uint  attr_size  = sizeof(Tn);
    sc_uint  elt_size   = sizeof(EltType);

private:
    // remember at least one elt has been split off from P
    static_assert( 0 <= k  &&  k <= sizeof...(P),  "k out of bounds" ); 
    
    struct Terminator {
        using destination = void;
        sc_uint  bytecount = 0;
        static void setup_gl(int, int) { cout << "...setup_gl done!" << endl; }
    };

    using This =    Recursor< k  , offset          , Tn, P... >;
    using Next = typename conditional<
                    k == 0,
                    Terminator,
                    Recursor< k-1, offset+attr_size,     P... >
                    >::type;

public:
    // usage: e.g. 
    //      using Ri = Recursor<i, 0, W>::destination;
    //      cout << Ri::offset;
    using destination = typename conditional< k == 0, This, typename Next::destination >::type;

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

    template< int k >  
    using A = typename R<k>::destination;
    
    template< int k >  using Tn      = typename A<k>::Tn;     // of form T[n], e.g. float[3]
    template< int k >  using EltType = typename A<k>::EltType;


    template <int k>
    using V = Vec< typename A<k>::EltType,  A<k>::dim >;

    // ATTRIBUTE 
    // Get
    template <int k>
    V<k> get() {
        static_assert( k>=0  &&  k<N,  "Attribute index out of range!" );
        V<k> ret;
        memcpy( &ret,  data + A<k>::offset,  A<k>::attr_size );
        return ret;
    }
    
    // Set
    template <int k>
    void set( void* src ) {
        cout << "set<" << k << ">( void* )" << endl << endl;
        static_assert( k>=0  &&  k<N,  "Attribute index out of range!" );
        memcpy( data + A<k>::offset,  src,  A<k>::attr_size );
    }
    
    template <int k> // need only this one!
    void set( V<k> const& ref ) { 
        cout << "set<" << k << ">( V<" << k << "> const& ref )" << endl; 
        set<k>( (void*)&ref ); 
    }
    
    template <int k>
    void set( Tn<k> const& ref ) { 
        cout << "set<" << k << ">( Tn<" << k << "> const& ref )" << endl; 
        set<k>( (void*)&ref ); 
    }
    
    // Attribute ELEMENT
    // Get
    template <int k, int e>
    EltType<k> const  get() {
        static_assert( k>=0 && k<N  &&  e>=0 && e < A<k>::dim,  "Attribute or Element index out of range!" );
        EltType<k> ret;
        memcpy( &ret,  data + A<k>::offset + e*A<k>::elt_size,  A<k>::elt_size );
        return ret;
    }
    
    // Set
    template <int k, int e>
    void set( const EltType<k>& ref ) {
        static_assert( k>=0 && k<N  &&  e>=0 && e < A<k>::dim,  "Attribute or Element index out of range!" );
        memcpy( data + A<k>::offset + e*A<k>::elt_size,  &ref,  A<k>::elt_size );
    } 
    
    template< int k, typename P0,  typename... Px >
    void set_all( P0 const&  p0,  Px const&  ... p )
    {
        set<k>( p0 );
        set_all<k+1>( p... );
    }
    
    template< int index >
    void set_all()
    { }
    
    Attribute() {}
    
    Attribute( P const& ... params ) {
        set_all<0>( params... );
    }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main()
{
    if((1)){
        using V = Attribute< int[2] >;
        
        COUT( sizeof(V) );
        COUT( V::total_bytes );
    
        V::setup_gl();
        {
            V v;
            int a0[2]{1,2};
            v.set<0>( a0 );
            
            COUT(( v.get<0,1>() ));
            
            v.set<0>( {3,4} );
            v.set<0>( a0 );
        }
        
        {
            cout << "test vw" << endl;
            V v( {1,2} );
            V w( {{1,2}} );
    
            auto a0 = v.get<0>();
            a0.u += 10;
            COUT(a0.u);
            v.set<0>( a0 );
            v.set<0>( {7,8} );
            v.set<0,1>( 9 );        COUT(( v.get<0,1>() ));
            v.set<0,1>( {10} );     COUT(( v.get<0,1>() ));
        }
    }

    if((1)){
        cout << "using V = Attribute< float[3], int[1], double[4] >;" << endl;
        using V = Attribute< float[3], int[1], double[4] >;
    
        COUT( V::A<0>::dim );
        COUT( V::A<1>::dim );
        COUT( V::A<2>::dim );
        
        V v(   {1.f,2.f,3.f}, {4}, {5.,6.,7.,8.}   );   COUT(( v.get<2,2>() )); // 7
        v.set<2>( { 50., 60., 70., 80. } );             COUT(( v.get<2,2>() )); // 70
        v.set<2,2>( 100 );                              COUT(( v.get<2,2>() )); // 100
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
