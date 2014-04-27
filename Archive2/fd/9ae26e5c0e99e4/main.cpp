    #include <iostream>
    #include <memory>
    #include <new>
    
    struct MyClass {
      char c;
      char d;
        virtual ~MyClass() {} // needed for introducing overhead
        void *operator new[](std::size_t count) {
            void *p = ::operator new[](count);
            std::cout << "allocating " << count << " bytes\n";
            return p;
        }
    };
    
    int main() {
      for( auto count : { 1, 5, 10, 20 } ) {
        std::cout << "allocating " << sizeof(MyClass) << " * " << count << " items\n";
        auto x = new MyClass[count];
        delete[] x;
      }
    }

