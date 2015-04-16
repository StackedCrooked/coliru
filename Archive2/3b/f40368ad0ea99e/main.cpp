    #include <iostream>
    #include <string>
    #include <exception>
    #include <cstdlib>
    
    #include <iostream>
    #define M(x, ...) __VA_ARGS__

    int a[] = { M(1'2, 3'4, 5) };

    struct foo { ~foo() { throw std::string("03"); } };

    void cpp_11() {
        std::cout << "11" << std::endl;
        std::exit(0);
    }
    int main() {
      std::cout << "C++";
      if (sizeof(a) > sizeof(int)) {
        std::cout << "14" << std::endl;
      } else {
        std::set_terminate(cpp_11); 
        try { foo c03_test; }
        catch( std::string c) {
          std::cout << c.c_str() << std::endl;
        }
      }
    }
