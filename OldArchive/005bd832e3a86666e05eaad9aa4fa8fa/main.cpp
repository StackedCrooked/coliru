#include <memory>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <type_traits>

using std::cout;
using std::endl;

template<int n1, int n2>
struct range
{
    template<typename T>
	struct rangeret
	{
		T& t;
		rangeret(T& _t): t(_t) { }

		decltype(std::begin(T())) begin() { return std::begin(t)+n1; }
		decltype(std::begin(T())) end() { return std::begin(t)+n2; }
        
        //rangeret(const rangeret&) = delete;
    	rangeret& operator=(const rangeret&) = delete;
	};
	
	template<typename T>
	friend rangeret<T> operator| (T& container, range)
	{
		return rangeret<T>(container);
	}
};

template<int n1, int n2, typename T>
auto make_range(T& container) -> decltype(container | range<n1, n2>())
{
    return container | range<n1, n2>();
}

int main()
{
	cout<<std::boolalpha;

	std::array<int, 5> arr = {1, 2, 3, 4, 5};
	std::vector<int> v;
	for(auto& i: arr)
		v.push_back(i);
        
    for(auto const& i: make_range<2, 4>(arr))
        cout<<i<<' ';
        
    cout<<endl;
        
    for(auto& i: v | range<2, 5>())
    	cout<<i<<' ';
}