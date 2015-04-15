#include <utility>

template<typename... Args>
struct helper
{
    template<typename F>
    static auto deduce(F&& f) -> decltype(f(std::declval<Args>()...));
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

#define OVERLOAD_SET(F) ([](auto&&... args) -> decltype(auto) { return F(std::forward<decltype(args)>(args)...); })

int main()
{
    auto fl = OVERLOAD_SET(fun);
    print_type< decltype(helper<int>::deduce(fl)) >();
}