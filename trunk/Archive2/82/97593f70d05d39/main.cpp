#include<iostream>
#include<string>
#include<utility>
#include<vector>

template <typename T, typename Pred>
void for_each(T t, const Pred& pred)
{
    auto local = std::vector<typename T::value_type>{t.begin(), t.end()};

    for (auto&& v : t)
        pred(v);
}

void pred(int c)
{
    std::cout << c << " ";
}

int main()
{
    auto arr { 1, 2, 3 };
    for_each(arr, pred);

    return 0;
}