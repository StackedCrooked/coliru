    #include <iostream>
    
    struct test {
      test ()  { std::cout << "test ()" << std::endl ; } 
      test (int)  { std::cout << "test (int)" << std::endl ; }
    };
    
    void func( test const &s = {} )
    {
    }
    
    int main()
    {
        test s = {} ;
        func() ;
    }