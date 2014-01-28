struct Traits {
    template <typename T>
    struct Foo {
        typedef typename T::bar* type;
    };
};

template <typename T>
class Bar
{
    typedef int bar;
    // need to make T::Foo<Bar> a friend somehow?
    
    using my_friend=typename T::template Foo<Bar>;
    
    friend my_friend;
    
    typedef typename T::template Foo<Bar>::type type; // won't compile because bar is private... 
                                                      // suppose I cannot make bar public.


    type val;
};

int main() {
    Bar<Traits> b;
}