#include <utility>

struct b
{
    explicit b(int) {}
};

struct d1 : b
{
    using b::b;
};

struct d2 : b
{
    template<class ... Args> 
    d2(Args&& ... args) : b((std::forward<Args>(args))...) {}
};

int main()
{
    {
//        d1 d = 10; // does not compile
    }
    {
        d2 d = 10;
    }
}
