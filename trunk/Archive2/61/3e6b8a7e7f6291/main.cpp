template<unsigned int n>
struct Factorial {
    enum { value = n * Factorial<n-1>::value};
};

template<>
struct Factorial<0> {
    enum {value = 1};
};


template<int factorial> 
struct _{ operator char() { return factorial + 256; } }; //always overflow

#define PRINT_AS_WARNING(constant) char(_<constant>())    

int main() 
{
         PRINT_AS_WARNING(Factorial<5>::value);
         return 0;
}