#include <string>
#include <limits>

typedef char char8_t; // just for symmetry.

#define charSz 16 // may by 16 or 32. change by hand !

//#define CONCAT_(a,b,c) a ## b ## c
//#define CONCAT(a,b,c) CONCAT_(a,b,c)
//typedef CONCAT(char,charSz,_t) Char; // may be char8_t or char16_t or char32_t 

#if charSz == 8
    #define STR(s) #s
    typedef char8_t Char;
#elif charSz == 16
    #define STR(s) u ## #s
    typedef char16_t Char;
#elif charSz == 32
    #define STR(s) U ## #s
    typedef char32_t Char;
#endif 

typedef int32_t Token;
typedef unsigned char byte;

typedef size_t addr;addr freePos=0;Token freeT=0;
const size_t heapSize=0x400;byte m[heapSize];

addr Allocate(size_t sz){addr t=freePos;freePos+=sz;return t;}
void Deallocate(addr p,size_t sz){/**((size_t*)(m+p))=sz;*/}

using namespace std;
template <typename T>
struct Allocator {
        // http://www.codeproject.com/Articles/4795/C-Standard-Allocator-An-Introduction-and-Implement

        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;

    typedef value_type& reference;typedef const value_type& const_reference;

    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template<typename U> struct rebind {typedef Allocator<U> other;};

    inline Allocator() {}
        // The initialization of freePos and freeT is done after the class definition.
        //  Doing it in the class creator ins't correct because another intializer of another Allocator
        // class would reinitialize that. 

    inline ~Allocator() {}
    inline Allocator(Allocator const&) {}
    inline addr address(reference r) {return (byte*)(&r)-m;}
    inline addr address(const_reference r) {return (byte*)(&r)-m;}

    //static inline offset_type allocate(size_type n, typename std::allocator<void>::const_pointer hint = 0)
    //  offset_type t=freePos;freePos+=n*sizeof(T);return t;
    static inline pointer allocate(size_type n){return (pointer)(m+Allocate(n*sizeof(T)));}

    static void deallocate(pointer p, size_type n){Deallocate((byte*)p-m,sizeof(T)*n);}

    inline size_type max_size() const{ 
       return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    inline void construct(pointer p, const T& t) {}
    inline void destroy(pointer p) {}

};

template <typename T>
    bool operator==(Allocator<T> const &, Allocator<T> const &) { return true; }
template <typename T>
    bool operator!=(Allocator<T> const &, Allocator<T> const &) { return false; }

typedef std::basic_string< Char,std::char_traits<Char>,Allocator<Char> > String;

int main(){
  for (size_t i=0;i<sizeof(m);i++) m[i]=0xDD; // fill memory to be able to see changes - especially 0s 

  String s=STR(nice) ;
  String t=STR(very nice) ;
  String u=STR(good) ;

    return 0;

}