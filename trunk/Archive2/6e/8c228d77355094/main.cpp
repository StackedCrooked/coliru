#include <iostream>
#include <tuple>

bool pred1(int x) { return x % 30 == 0; }
bool pred2(int x) { return x % 15 == 0; }
bool pred3(int x) { return x %  5 == 0; }

void fun1(int x) { std::cout << "divisible by 30 \n"; }
void fun2(int x) { std::cout << "divisible by 15 \n"; }
void fun3(int x) { std::cout << "divisible by  5 \n"; }

void fun(int x)
{
    if (pred1(x)) { 
        fun1(x);
        fun2(x);
        fun3(x);
        return;
    }
    if (pred2(x)) {
        fun2(x);
        fun3(x);
        return;
    }
    if (pred3(x)) 
        fun3(x);
}

using Triple = std::tuple<bool, bool, bool>;

auto preds(int x) -> Triple
{
    if (pred1(x)) return Triple{ true,  true, true };
    if (pred2(x)) return Triple{ false, true, true };
    return Triple{ false, false, pred3(x) };
}

void gun(int x)
{
    auto const p = preds(x);
    if (std::get<0>(p)) fun1(x);
    if (std::get<1>(p)) fun2(x);
    if (std::get<2>(p)) fun3(x);
}

int main()
{
    std::cout << "Starting fun:\n"; fun(30); std::cout << "\n";
    std::cout << "Starting gun:\n"; gun(30); std::cout << "\n";
}
