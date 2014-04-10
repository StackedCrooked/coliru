#include <type_traits>

template <class T, bool b> struct AssertionBase {
            static_assert(b, "I take only floats, you fool");
};

template <class T> struct Foo : AssertionBase<Foo<T>, false> {
    
    static void my_func() 
    {
    }
}; 

template <> struct Foo<float> : AssertionBase<Foo<float>, true> {
    static void my_func() 
    {
        
    }
};


int main() 
{
    Foo<float>::my_func();
    //Foo<int>::my_func();
}
