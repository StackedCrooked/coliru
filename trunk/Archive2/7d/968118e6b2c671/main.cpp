#include <iostream>
#include <functional>


using namespace std;

template<typename F>
class tester
{
    function<F> func;
public:
    template <typename H, typename... Args>
    tester(H &&f, Args&&... args) : func(bind(f, args...))
    {
    }

    ~tester()
    {
        cout << func();
    }
};

class Specimen
{
public:
    int testFunc(int a, float b)
    {
        return a + b;
    }
};

int main()
{
    Specimen sObj;

    tester<int()> myTestObj(&Specimen::testFunc, &sObj, 10 , 190);
}