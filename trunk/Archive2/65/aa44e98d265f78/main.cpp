#include <iostream>
using namespace std;

template <typename T>
class Foo // wrapper class for a POD
{
    T val_; // this is the wrapped value
public:
    Foo(T val = {}): val_(val) {};

    //template<typename S> // conversion operator
    operator T ()
    {
        std::cout << "Calling conversion operator" << std::endl;
        return val_;
    }

    // the += operator
    Foo& operator+=(const Foo& rhs)
    {
        val_ += rhs.val_; 
        return *this;
    }

    // the + operator
    friend Foo operator+(Foo lhs, const Foo& rhs)
    {
        cout << "Calling operator+" << endl;
        return lhs += rhs;
    }

    // stream operator
    friend std::ostream &operator<<(std::ostream &os, const Foo &rhs)
    {
        return os << rhs.val_;
    }
};

int main()
{
    Foo<int> a = 10;

    // operator+(2.1, a), why not
    // 2.1 + a. operator int() ?
    cout << 2.1 + a << endl; // outputs 12
}