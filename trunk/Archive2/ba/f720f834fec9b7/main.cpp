#include <iostream>
using std::cout;
using std::endl;

    void test_ptr(std::nullptr_t)
    {
      std::cout << "nullptr" << std::endl;
    }
    void test_ptr(double *d)
    {
      std::cout << *d << std::endl;
    }
    
    template<typename T>
    void test(T d)
    {
      test_ptr(d);
    }
    
    int main()
    {
      test(nullptr);
    }