template<typename... Args>
struct helper
{
    template<typename R>
    static auto deduce(R(*)(Args...)) -> R(*)(Args...);
};

#include <iostream>
template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

using namespace std;

void fun(int a) {
    cout << "void fun(int a) : " << a << endl;
}

void fun(double a) {
    cout << "void fun(double a) : " << a << endl;
}

int main()
{
    print_type< decltype(helper<int>::deduce(fun)) >();
}