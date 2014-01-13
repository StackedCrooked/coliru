#include <iostream>

template<typename T>
struct X
{
    T val;
};

template<typename F, typename T>
auto operator >>= (X<T> const& x, F f)
{
    return f(x.val);
}


int main()
{
    X<int> x{42};
    auto a = [] (int i) { return X<bool>{true}; };
    auto b = [] (bool b) { return X<char>{'c'}; };
    
    auto res = (x >>= a) >>= b;
    std::cout << res.val;
}
    