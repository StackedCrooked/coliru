#include <algorithm>

auto min1 = [](int a, int b) { return b < a ? b : a; };
auto min2 = [](int a, int b) { return b < a ? b : a; };
auto min3 = [](int a, int b) { return b < a ? b : a; };
auto min4 = [](int a, int b) { return b < a ? b : a; };


int main()
{
    return min1(min2(min3(min4(22222, 55555), 11111), 44444), 33333);
}
