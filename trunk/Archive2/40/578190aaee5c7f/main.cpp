#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct aa{
    int a;
    bool b;
};

int main()
{
    aa test;
    test.a = 1;
    test.b = true;
    auto m1 = test.a;
    std::cout << m1 << std::endl;
    
    auto n = [](int x, int y){return x + y;}(4, 5);
    std::cout << n << std::endl;
    
    auto f = [](int x, int y){return x + y;};
    std::cout << f(5, 5) << std::endl;
    
    int x = 6;
    int y = 7;
    auto f1 = [&](){x = x + 1;return x + y;};
    std::cout << f1() << std::endl;
    std::cout << " x=" << x << " y=" << y << std::endl;
    
    auto f2 = [=](){return x + y;};
    std::cout << f2() << " x=" << x << " y=" << y << std::endl;
    
    int m = [](int x){ return [](int y) { return y * 2; }(x) + 3; }(5);
    std::cout << m << std::endl;
    
    
    
    int a[10] = {0}; 

    srand(time(NULL));

    generate(a,a+10,[]()->int { return rand() % 100; });

    std::cout<<"before sort: "<<std::endl;

        for_each(a, a+10, [&](int i){ std::cout<< i <<" "; });

 

    std::cout<<std::endl;

    std::cout<<"After sort"<<std::endl;

    sort(a,a+10);

    for_each(a, a+10, [&](int i){ std::cout<< i <<" "; }); 

}
