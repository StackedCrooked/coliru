#include <set>
#include <iostream>

//not real comparators, I know
struct A {
    int i = 0;
    bool operator()(int a, int b)
    {
        ++i;
        return a < b;
    }
};

int main()
{    
    A a;
    std::set<int, A&> s1( {1, 2, 3}, a);
    std::set<int, A&> s2( {4, 5, 6}, a);
    std::cout << a.i;
}