#include <iostream>
#include <initializer_list>
using namespace std;

initializer_list<int> test()
{
    int a = 1;
    auto il = {a++, a++, a++, a++};
    for (auto x: il) cout<<x<<' ';
    return il;
}

int main()
{
    auto il = test(); cout<<endl;
    for (auto x: il) cout<<x<<' ';
	return 0;
}