#include <iostream>
#include <functional>
#include <vector>
#include <iostream>
#include <vector>
using namespace std;
void test(){}
template<typename T,typename...Args>
void test(T v,Args... args)
{
    std::cout<<v;
    test(args...);
}

template<typename T,typename...Args>
constexpr auto test2 = test(T v,Args... args)
{
}
        
int main()
{
    test2(4,7);
}
