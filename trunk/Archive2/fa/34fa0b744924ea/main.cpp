#include <iostream>
#include <string>
typedef unsigned long long  ul64;
double m[10] = { 65.45433, 45435.0054, 232543535.9, 0.00043543, 99.99999, 5345434.000, 754354.6, 80008.243, 0.9, 10.01 };
union foo
{
    char cs[8];
    double x;
    ul64 a;
    foo(std::string s) { for (int i = 0; i < s.size(); i++) cs[i] = s[i];}
    foo(double y) :x(y){}
    foo(ul64 b) :a(b){}
};
int main()
{
    foo bar(0xe8e711395e65686dull);
    for (int i = 1; i <= 10; i++)
        bar.x *= m[i];
    for (int i = 1; i <= 8; i++)
        std::cout << bar.cs[i];
    std::cout << std::endl;
    return 0;
}