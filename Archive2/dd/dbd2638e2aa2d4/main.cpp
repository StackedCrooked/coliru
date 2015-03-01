#include <string>
#include <iostream>

using namespace std;


// http://en.cppreference.com/w/cpp/types/offsetof
#define offsetof2(type,member) ((std::size_t) &(((type*)0)->member))

template < typename Tn, typename ...P >
struct Vertex
{
    // want:
    //   Vertex<...P>  v;
    // unless termination (in which case int)
    conditional< (sizeof...(P)>0), Vertex<P...>, int >  v;

    // split Tn into T[n]
    // http://en.cppreference.com/w/cpp/types/extent
    using T = typename decay<Tn>::type;
    static constexpr  unsigned int  n = extent<Tn>::value;
    
    T t[n];
    
    using U = Vertex<Tn, P...>;
    
    static constexpr unsigned int byteoffset2 = offsetof2( U, t );
    static constexpr unsigned int byteoffset = offsetof( U, t );
};

int main()
{
    using V = Vertex< float[3],  int[2],  double[4] >;
    cout << sizeof(V);
}