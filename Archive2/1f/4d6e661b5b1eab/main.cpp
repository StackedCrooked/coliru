#include <iostream>

using namespace std;

static const struct Aux
{
    template<typename F>
    struct Guard
    {
        const F& f;

        Guard(const Guard&) = delete;
    
        Guard(const F& f) : f(f) {}
        ~Guard() noexcept(noexcept(f()))
        {
            f();
        }
    };

    template<typename F>
    Guard<F> operator*(const F& f) const
    {
        return {f};
    }
} aux{};

struct Test
{
    void operator()() const
    {
        cout << "Test::operator()" << endl;
    }
    ~Test()
    {
        cout << "Test::~Test()" << endl;
    }
};

int main()
{
    auto&& guard1 = aux * Test{};
    cout << "begin of scope\n";
}