#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

std::string createString()
{
    return "I have been passed out by value.";
}

std::vector<int> createVector()
{
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }
    return vec;
}

int main(int, char**)
{
    auto str = createString();
    puts(str.c_str());

    auto vec = createVector();
    std::for_each(std::begin(vec), std::end(vec), [](int i)
    {
        printf("%d ", i);
    });
    puts("");
}
