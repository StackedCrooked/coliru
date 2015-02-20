#include <iostream>
union T
{
    int y{1};
    float x;
    char c;
    T() = default;
};

int main()
{
    T t;
    std::cout << t.y << '\n';
}
