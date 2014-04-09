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
    
    std::set<int, A&> s1(a);
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    
    std::set<int, A&> s2(a);
    s2.insert(4);
    s2.insert(5);
    s2.insert(6);
    
    std::cout << a.i;
}