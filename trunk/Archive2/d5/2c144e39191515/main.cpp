#include <iostream>

namespace M {
    class B {
        public:static const int i = 1000;
    };
}

namespace N {
    class Y /*: public M::B*/ {
            
        class X {
            int a[i];
            static const int i = 1;

        public:
            X() { for(int j = 0; j < i; ++j ) a[j] = 1; }
            static int Get() { return i; }
        };
        public:
        int Get() { return X::Get(); }
    };
}



int main()
{
    N::Y y;
    std::cout << y.Get() << '\n';
}