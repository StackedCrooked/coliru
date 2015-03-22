#include <iostream>
#include <algorithm>

int main()
{
    auto f = [](int i){return i+1;};
    auto g = [](int i){return i-1;};
    auto a = true ? static_cast<int(*)(int)>(f) : +g;
}
