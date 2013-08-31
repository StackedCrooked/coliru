#include <iostream>

using namespace std;

template <typename Func>
class Command
{
    Func m_func;
public:
    Command(Func f) : m_func(f) { }

    template <typename... A> auto operator()(A... args) const 
        -> decltype(m_func(args...)) 
    { return m_func(args...); }
};

template <typename Func> Command<Func> make_command(Func f)
{
    return Command<Func>(f);
}

void testFunction(int i, double d)
{
    std::cout << "TestFunctor::operator()(" << i << ", " << d << ") called." << std::endl;
}

int main()
{
    auto command = make_command(testFunction);
    command(1, 3.14);
}
