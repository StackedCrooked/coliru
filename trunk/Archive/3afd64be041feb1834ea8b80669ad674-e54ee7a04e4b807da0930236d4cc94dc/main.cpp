  #include <iostream>

namespace N {
    template<typename T> struct A {
        void f(A *) { std::cout << "A" << std::endl; } // would take this with V2
    };
}
void f(void*) { std::cout << "B" << std::endl; } // would take this with V1

namespace N
{
/* V1: */ template<> struct A<int>;
}

int main() {
  N::A<int> *p = 0;
  f(p);
}

namespace N
{
/* V2: */ template<> struct A<int>;
}

