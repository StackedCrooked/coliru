#include <iostream>

using namespace std;

template<typename FUNCTION, typename... ARGS>
decltype(auto) wrapper(FUNCTION&& func, ARGS&&... args)
{
    cout << "WRAPPER: BEFORE" << endl;
    auto res = func(args...);
    cout << "WRAPPER: AFTER" << endl;
    return res;
}

int dummy(int a, int b)
{
    cout << a << '+' << b << '=' << (a + b) << endl;
    return a + b;
}

int main(void)
{
    dummy(3, 4);
    cout << "WRAPPERS RES IS: " << wrapper(dummy, 3, 4) << endl;
}