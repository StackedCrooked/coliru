#include <functional>
#include <iostream>

template<typename F1>
auto make_composite_function(F1&& f1)
{
    return std::bind(std::forward<F1>(f1), std::placeholders::_1);
}

template<typename F1, typename... Fn>
auto make_composite_function(F1&& f1, Fn&&... fn)
{
    return std::bind(std::forward<F1>(f1), make_composite_function(std::forward<Fn>(fn)...));
}

int main(int argc, char* argv[]) {
    using namespace std;
    auto f1 = [] (int x) { cout << "f1" << endl; return x; };
    auto f2 = [] (int x) { cout << "f2" << endl; return x; };
    auto f3 = [] (int x) { cout << "f3" << endl; return x; };
    make_composite_function(f1, f2, f3)(1);
}
