#include <iostream>

class Derp {
    public:
        void print() 
        {
            std::cout << "DERP" << std::endl;
        }
};

class Herp {
    public:
        void print() {
            std::cout << "HERP" << std::endl;
        }
};

class Foo {
    public:
        template <class T>
        void print(T adsf) {
            adsf.print();
        }
};

int main() {
    Derp derp;
    Herp herp;

    Foo foo;
    foo.print<Herp>(herp);

    return 0;
}
