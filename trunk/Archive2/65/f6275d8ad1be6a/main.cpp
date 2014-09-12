#include <iostream>
#include <map>

template <typename T>
struct reverse_t
{
    T& t;
    reverse_t(T& m) : t{m} {}
    decltype(t.rbegin()) begin() { return t.rbegin(); }
    decltype(t.rend()) end() { return t.rend(); }
};

template <typename T>
reverse_t<T> reverse(T& t)
{
    return reverse_t<T>{t};
}

int main()
{
    std::map<int, int> m{ {1,1}, {2,2}, {3,3} };
    for (const auto& p : reverse(m))
    {
        std::cout << p.second << std::endl;
    }
}
