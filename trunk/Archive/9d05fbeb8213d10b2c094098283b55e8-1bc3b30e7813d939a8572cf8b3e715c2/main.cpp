#include <algorithm>

class Outer
{
    struct Inner
    {
        int a;
        void swap(Inner &other)
        {
            using std::swap;
            swap(this->a, other.a);
        }
    };
    
    friend void std::swap<Inner>(Inner&, Inner&) noexcept;
public:
    static void test();
};

namespace std
{
    template<> void swap<Outer::Inner>(Outer::Inner &a, Outer::Inner &b) noexcept
    { a.swap(b); }
}

void Outer::test()
{
    using std::swap;
    Inner a, b;
    swap(a, b);
}

int main()
{
    Outer::test();
    return 0;
}