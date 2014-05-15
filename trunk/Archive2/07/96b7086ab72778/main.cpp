#include <iostream>

class A
{
private:
    int t;

public:
    template <typename B>
    A(B b) : t(b)
    {
        std::cout << t << '\n';
    }

};

template <> A::A(int b) {
    t = b;
    std::cout << __LINE__ << ": " << t << '\n';
}

template <> A::A(double b) {
    std::cout << __LINE__ << ": " << b << '\n';
}


int main()
{
    A a(777u);
    A b{ 666 };
    A c{ 888.1 };
    return 0;
}