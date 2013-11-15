    template<typename T> void baz(T*) {}
    /*template<typename T> struct TemplatingHelper {
      typedef void (*foo_t)(T*);
      static constexpr foo_t dummy = baz;
    };
    
    template<typename T>                   // template-declaration
    typename TemplatingHelper<T>::foo_t    // type
    TemplatingHelper<T>::dummy             // name
    = baz;                                 // initializer*/
    
    struct TemplatingHelper
    {
        typedef void (*foo_t)(int*);
        static const foo_t dummy;
    };
    
    decltype(TemplatingHelper::dummy)
    TemplatingHelper::dummy
    = baz;
    
    #include <type_traits>
    int main()
    {
        int i;
        TemplatingHelper/*<int>*/::dummy(&i);
        //static_assert(std::is_same<decltype(TemplatingHelper<int>::dummy), TemplatingHelper<int>::foo_t>{}, "!");
    }