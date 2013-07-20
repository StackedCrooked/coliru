#include <iostream>

using namespace std;

template <typename Func, typename ReturnType, typename... Arguments>
class Command
{
public:
    Command(Func f) : m_func(f) { }
    ReturnType operator()(Arguments... funcArgs) { return m_func(funcArgs...); }
private:
    Func m_func;
};

void testFunction(int i, double d)
{
    std::cout << "TestFunctor::operator()(" << i << ", " << d << ") called." << std::endl;
}

int main()
{
    void (&fRef)(int, double) = testFunction;
    Command<void(*)(int, double), void, int, double> testCommand(fRef);
    testCommand(1, 3.14);
}
