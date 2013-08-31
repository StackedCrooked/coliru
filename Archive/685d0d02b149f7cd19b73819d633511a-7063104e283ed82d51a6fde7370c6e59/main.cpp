#include <cstdio>
#include <iostream>
#include <utility>

struct AA
{   
    // Here's your... .. virtual function version that uses moves isntead
    // of copies
    inline static void test(AA&& aa) __attribute__((always_inline))
    {
        AA* ptr =   new AA( std::move( aa ) );
        delete ptr;
    }
    // Here's the constructor-forwarding version
    template <typename ...Tn>
    static void testvariadic( Tn&&... argn )
    {
        // The '&&' syntax when used with templates means
        // 'universal reference'. It means it can be anything
        // it will match almost any kind of function
        // right out of the bat
        // be careful when you make these!
        AA* ptr =   new AA( std::forward<Tn>( argn )... );
        delete ptr;
    }

    AA(AA const& aa)
    {
        printf("COPY!\n");
    }

    AA(AA&& aa)
    {
        xx = aa.xx;
        aa.xx = 0;
        printf("GET MOVED!\n");
    }
    
    AA(int v)
    {
        printf("CTOR!\n");
        xx  =   v;
    }

    int xx  =   55;
};

int main(int argc, const char * argv[])
{
    

    // Test one
    printf( "Test I:\n" );
    AA::test(AA(77));
    printf( "\n" );
    // Variadic test
    printf( "Test II:\n" );
    AA::testvariadic( 77 );
    printf( "\n" );
    return 0;
}
