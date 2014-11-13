#include <iostream>
#include <functional>
using namespace std;

class A
{
public:
    A(int inI, int inJ) : _i(inI), _j(inJ)
    {
        create_functor();
    }

    A(const A& rtSide) : _i(rtSide._i),_j(rtSide._j)
    {
        create_functor();
    }

    A(A&& rtSide) : _i(rtSide._i), _j(rtSide._j)
    {
        rtSide.f = nullptr;
        create_functor();
    }

    A& operator=(A&& rtSide)
    {

        _i = rtSide._i;
        _j = rtSide._j;
        create_functor();

        rtSide.f = nullptr;

        return *this;
    }

    A& operator=(A& rtSide)
    {
        if (this == &rtSide)
            return *this;

        _i = rtSide._i;
        _j = rtSide._j;
        create_functor();

        rtSide.f = nullptr;

        return *this;
    }

    ~A() {}

    void reset_i(const int& newI) { _i = newI; }

    function<double(const double&)> f;

private:
    void create_functor()
    {
        std::reference_wrapper<int> r = _i;
        f = [r](const double& inX) -> double {return inX * static_cast<double>(r); };
    }

    int _i;
    int _j;
};

int main()
{

    A _A1(2,0);
    A _A2(1,0);

    _A2 = _A1;

    cout << _A2.f(2) << endl;

    _A2.reset_i(4);

    cout << _A2.f(2) << endl;

    return 0;
}