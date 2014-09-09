#include <iostream>

using namespace std;

bool fun(int a)
{
    cout << "fun(int)" << endl;
    return true;
}

bool fun(const char *s)
{
    cout << "fun(char*)" << endl;
    return true;
}

bool fun(bool b)
{
    cout << "fun(bool)" << endl;
    return b;
}

template<typename... Args>
inline void pass(Args&&...)
{
}

template<typename... Args>
inline void expand(Args&&... args)
{
    pass(fun(args)...);
}

int main()
{
    expand(42, "answer", true, false);
    return 0;
}
