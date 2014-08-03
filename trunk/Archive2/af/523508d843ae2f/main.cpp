#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
class Foo // wrapper class for a POD
{
    T val_; // this is the wrapped value
public:
    Foo(T val = {}): val_(val) {};

    template<typename S, std::enable_if_t<std::is_same<S, int>::value>* = nullptr > // conversion operator
    operator S ()
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
    cout << 2 + a << endl; // outputs 12
}