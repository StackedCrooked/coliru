#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Test
{
    int a;
    int b;
};

template <class Iterator>
void ApplySomething(Iterator start, Iterator end)
{
    std::transform(start, end, start, [] (const Test& t) {
        Test t2 { t.a + 1, t.b };
        return t2;
    });
}

int main()
{
    std::vector<Test> vec;
    Test t = { 1, 2 };
    vec.push_back(t);
    std::cout << vec[0].a << " " << vec[0].b << std::endl;
    ApplySomething<std::vector<Test>::iterator>(vec.begin(), vec.end());
    std::cout << vec[0].a << " " << vec[0].b << std::endl;
    std::list<Test> lst;
    lst.push_back(t);
    std::cout << lst.front().a << " " << lst.front().b << std::endl;
    ApplySomething<std::list<Test>::iterator>(lst.begin(), lst.end());
    std::cout << lst.front().a << " " << lst.front().b << std::endl;
    return 0;
}