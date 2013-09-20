    #include <type_traits>
    
    class BASE_Y {};
    class BASE_X {};
    
    struct A {
      template<class T, class = void>
      class S;
    
      template<class T>
      class S < T, typename std::enable_if< std::is_base_of< BASE_Y, T >::value >::type > {};
    
      template<class T>
      class S < T, typename std::enable_if< std::is_base_of< BASE_X, T >::value >::type > {};
    };
    
    class D : BASE_X {};
    
    /*
    class B
    {
        template<class T>
        class S;
    
        template<>
        class S < BASE_Y > {};
    
        template<class T>
        class S < BASE_X > {};
    };
    */
    
    int main()
    {
      A::S< D > asd;
    }