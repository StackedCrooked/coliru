    template<typename T = void>
    class A {
    
    };
    
    #define A A<>
    
    auto main() -> int {
      A a;
      return 0;
    }