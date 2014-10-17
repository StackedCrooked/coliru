#include <algorithm>

int main()
{
    int x = 1, y = 2;
    int&(*f)(int&,int&) = std::min<int&>;
    f(x,y) = 3;
}