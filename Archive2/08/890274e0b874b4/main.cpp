#include <iostream>
#include <algorithm>

int main()
{
    auto f = [](auto i){return i+1;};
    auto g = [](auto i){return i-1;};
    auto a = true ? f : g;
}
