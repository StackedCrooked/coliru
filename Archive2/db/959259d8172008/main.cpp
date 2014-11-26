#include <iostream>

template<typename T>
inline T proper_mod(T x, T y)
{ return ((x % y) + y) % y; }

template<int L, int H>
class bounded_int
{
public:
    bounded_int(int f) : value(f)
    { fix(); }

    bounded_int(): bounded_int(0) {};

    bounded_int& operator=(int from)
    {
        value = from;
        fix();
        return *this;
    }

    operator int() const
    { return value; }

private:
    int value;

    void fix()
    {
        constexpr int range = H - L + 1;
        value = proper_mod(value - L, range) + L;
    }
};


int main()
{
    bounded_int<1, 6> x;
    bounded_int<-5, 5> y = 11;
    y = y + 10;
    std::cout << x << ' ' << y << '\n';
    y = y + 7;
    x = y;
    std::cout << x << ' ' << y << '\n';
}