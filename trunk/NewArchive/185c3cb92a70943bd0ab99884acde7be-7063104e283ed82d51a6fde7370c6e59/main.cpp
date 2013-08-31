#include <cstdio>
#include <iostream>
#include <utility>

struct AA
{   
    // Now, we replace the next time with a variadic-forwarding type
    //inline static void test(AA aa) __attribute__((always_inline))
    
    template <typename ...Tn>
    static void test( Tn&&... argn )
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
    AA(int v)
    {
        printf("CTOR!\n");
        xx  =   v;
    }

    int xx  =   55;
};

int main(int argc, const char * argv[])
{
    

    // This line gets reduced
    //AA::test(AA(77));
    // to
    AA::test( 77 );
    return 0;
}
