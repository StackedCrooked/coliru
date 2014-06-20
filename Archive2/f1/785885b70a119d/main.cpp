#include <iostream>
#include <functional>
#include <vector>
#include <iostream>
#include <vector>
using namespace std;
void test(int){}

template<typename T,typename...Args>
void test(int& sum,T v,Args... args)
{
    sum+=v;
    test(sum,args...);
}

auto sum = [](auto&&... pp) { return test(std::forward<decltype(pp)>(pp)...); };
int main()
{
    int val=0;
    sum(val,4,7);
    std::cout<<val;
}
