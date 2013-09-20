#include <cstdio>
#include <vector>

template <typename T, typename Func>
void ExecuteForAll(T container, Func functor)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        functor(*it);
    }
}

int main(int, char**)
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    ExecuteForAll(vec, [](int i)
    {
        if (i % 2)
        {
             i = - i;
        }
        printf("%d ", i);
    });
    puts("");

    return 0;
}
