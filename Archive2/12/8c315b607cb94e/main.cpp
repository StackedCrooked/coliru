    #include <type_traits>
    #include <iostream>
    
    class BASE_Y {};
    class BASE_X {};
    
    struct A {
      template<class T, class = void>
      class S;
    
      template<class T>
      struct S < T, typename std::enable_if< std::is_base_of< BASE_Y, T >::value >::type > 
      {
        int i = 0;
      };
    
      template<class T>
      struct S < T, typename std::enable_if< std::is_base_of< BASE_X, T >::value >::type > 
      {
        int i = 1;
      };
    };
    
    class D : BASE_X {};
    
    
    class B
    {
        template<class T>
        class S;
    
        template<>
        class S < BASE_Y > {};
    
        template<>
        class S < BASE_X > {};
    };
    
    
    int main()
    {
        A::S< D > asd;
        std::cout << asd.i << std::endl;
    }