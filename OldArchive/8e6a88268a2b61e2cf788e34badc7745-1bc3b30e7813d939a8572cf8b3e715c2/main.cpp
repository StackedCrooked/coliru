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
    
    friend void swap(Inner& L, Inner& R)
    {
        L.swap(R);    
    }
public:
    static void test();
};

void Outer::test()
{
    Inner a, b;
    swap(a, b);
}
int main()
{
    Outer::test();
    return 0;
}