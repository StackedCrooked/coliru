#include <iostream>
using namespace std;

struct non_default_constructible
{
    non_default_constructible() = delete;
    int x;
};

template <class T>
struct dummy
{
    T new_t()
    {
        return T{};
    }
};

int main()
{
    dummy<non_default_constructible> d;
    auto ndc = d.new_t();
    
    (void)ndc;
}
