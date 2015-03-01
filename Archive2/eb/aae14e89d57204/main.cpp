#include <string>
#include <iostream>

using namespace std;

// http://en.cppreference.com/w/cpp/types/offsetof
//#define OFFSET_OF(type_,member)  (size_t) & ((type_*)0)->member

template < int attribute_index, typename Tn, typename ...P >
struct Vertex
{
    using This = Vertex< attribute_index  , Tn, P... >;
    using Rem  = Vertex< attribute_index+1,     P... >;
    
    // want:
    //   Vertex<...P>  v;
    // unless termination (in which case int)
    Rem remainingAttributes;

    // split Tn into T[dim]
    // http://en.cppreference.com/w/cpp/types/extent
    using Type = typename decay<Tn>::type;
    static constexpr  unsigned int  dim = extent<Tn>::value;
    
    Type data[dim];
    
    static constexpr unsigned int bytelength = sizeof(data);
    static constexpr size_t       byteoffset = &  ((This*)nullptr) -> data;
    
    void setup() {
        //glEnableVertexAttribArray( attribute_index );
        
        //generic_glVertexAttribPointer< Type >(
        //    attribute_index,
        //    dim,
        //    bytelength,
        //    byteoffset
        //    );
        
        cout << dim << endl;
        
        remainingAttributes.setup();          
    }    
};

template<int attribute_index>
struct Vertex <>
{
    void setup() { cout << "term" << endl; }
};

int main()
{
    using V = Vertex< 0, float[3],  int[2],  double[4] >;
    cout << sizeof(V);
}