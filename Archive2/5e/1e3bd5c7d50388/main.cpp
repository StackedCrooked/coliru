#include <type_traits>



template <class T> struct Foo {
    
    static void my_func() 
    {
        static_assert(false, "I take only floats, you fool");
    }
}; 

template <> struct Foo<float> {
    static void my_func() 
    {
        
    }
};

int main() 
{
    Foo<float>::my_func();
}
