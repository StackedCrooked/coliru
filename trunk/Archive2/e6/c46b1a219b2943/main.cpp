#include <iostream>
#include <utility>

template<class T>
class parse
{
public:
    // parse will modify a local copy or move of its input parameter
    void operator()(T const& arg, int n) const { /* optimized for lvalues */ }
    void operator()(T&& arg     , int n) const { /* optimized for rvalues */ }
};

template<class T>
void accept(T&& arg)
{
    parse<T>()(std::forward<T>(arg), 0); // copy or move, depending on rvaluedness of arg
}

int main() {
    accept(0);
    auto x = 0;
    accept(x);
}
