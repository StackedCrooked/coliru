#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Test
{
    int a;
    int b;
};

const auto test_functor = [] (const Test& t) {
    Test t2 { t.a + 1, t.b };
    return t2;
};


int main()
{
    std::vector<Test> vec;
    Test t = { 1, 2 };
    vec.push_back(t);
    std::cout << vec[0].a << " " << vec[0].b << std::endl;
    std::transform(vec.begin(), vec.end(), vec.begin(), test_functor);
    std::cout << vec[0].a << " " << vec[0].b << std::endl;
    std::list<Test> lst;
    lst.push_back(t);
    std::cout << lst.front().a << " " << lst.front().b << std::endl;
    std::transform(lst.begin(), lst.end(), lst.begin(), test_functor);
    std::cout << lst.front().a << " " << lst.front().b << std::endl;
    return 0;
}