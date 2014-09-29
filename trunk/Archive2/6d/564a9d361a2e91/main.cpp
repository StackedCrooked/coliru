#include <type_traits>


class C
{
public:
    constexpr C(bool b) : C(b ? C(40, 2) : C(51)) {}
    constexpr C(int a, int b) : i( a + b) {}
    constexpr C(int a) : i(a) {}

    constexpr int get() const { return i; }
    void set(int a) { i = a; }
private:
    int i = 0;
};


int main()
{
    constexpr C cb(true);
    constexpr C cf(false);
    C cc(cf);

    cc.set(42);
}
