#include <cstdio>

#define stringify_macro(s) stringify(s)
#define stringify(s) #s

#define FILELINE() __FILE__ "|" stringify_macro(__LINE__)

#define PRAGMA(x) _Pragma(#x)
#define PRAGMA_MESSAGE(x) PRAGMA(message(x))

#define TEMPLATE_CLASS(name) PRAGMA_MESSAGE("class|" stringify(name) "|" FILELINE())
#define TEMPLATE_FUNCTION(name) PRAGMA_MESSAGE("function|" stringify(name) "|" FILELINE())


template <typename T>
struct Foo {
    TEMPLATE_CLASS(Enter_Foo)
    template <typename U>
    struct Bar {
        TEMPLATE_CLASS(Enter_Bar)
        
        TEMPLATE_CLASS(Exit_Bar)
    };
   TEMPLATE_CLASS(Exit_Foo)
};


int main() {
    PRAGMA_MESSAGE("Hi! xD")
    TEMPLATE_FUNCTION(main)
    
    Foo<int> foo_i;
    Foo<float> foo_f;

    return 0;
}