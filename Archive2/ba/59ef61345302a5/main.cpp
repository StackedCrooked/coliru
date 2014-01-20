    #include <iostream>
    #include <initializer_list>
    
    struct test {
      test ()  { std::cout << "test ()" << std::endl ; };
      
      test (int)  { std::cout << "test (int)" << std::endl ; };
      test ( std::initializer_list<int>) { std::cout << "test (initializer_list<int>)" << std::endl ; } ;
    };
    
    void func( test const &s = {0} )
    {
    }
    
    int main()
    {
        test s = {} ;
        func() ;
    }