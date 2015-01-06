#include <iostream>

template <int N, void* ptr = nullptr>
struct S
{
    S(void* p = nullptr) {}
    void f(){}
};

template <int N>
struct S<N, nullptr>
{
    S(void* p = nullptr) {}
    void f(){std::cout << std::hex << 65 << std::endl << 66 << std::endl << std::dec << 67 << std::endl;    }
};

int main ()
{
    S<10> s;
    s.f();
    
    S<200> s2(&s);
    
    std::cout << std::hex << 65 << std::endl << 66 << std::endl << std::dec << 67 << std::endl;    
  return 0;
}
