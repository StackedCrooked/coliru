#include <iostream>
#include <future>
#include <numeric>
#include <vector>

using namespace std;

struct Wrapper
{
    template<typename Fun>
	decltype(auto) callOn(Fun f)
	{
		return f(i);
	}
	
	int i = 10;	
};

int main()
{
    auto ii = Wrapper{}.callOn([] (int& i) { i*=20; return i;});
    cout << ii << endl;
    return 0;
}