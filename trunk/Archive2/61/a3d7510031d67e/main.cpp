#include <iostream>
#include <future>
#include <numeric>
#include <vector>

using namespace std;

template<typename T>
struct Wrapper
{
    Wrapper(T wrapped)
        : m_obj{move(wrapped)}
    {
    }
    
    template<typename Fun>
	decltype(auto) callOn(Fun f)
	{
		return f(m_obj);
	}
private:
	T m_obj;	
};

int main()
{
    Wrapper<int> wrapper{10};
    
    auto ii = wrapper.callOn([] (int& i) { i*=20; return i;});
    cout << ii << endl;
    return 0;
}