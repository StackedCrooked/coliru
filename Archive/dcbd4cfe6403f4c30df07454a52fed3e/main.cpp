#include <memory>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <type_traits>

using std::cout;
using std::endl;

namespace adlcheck
{
    using std::begin;
    
    template<typename T>
    auto adl_begin(T&& container) -> decltype(begin(container))
    {
        return begin(container);
    }
}

template<int n1, int n2>
struct range
{    
    template<typename T>
	struct rangeret
	{   
		T& t;
		rangeret(T& _t): t(_t) { }

        auto begin() -> decltype(adlcheck::adl_begin(t))  { auto ret = adlcheck::adl_begin(t); std::advance(ret, n1); return ret; }
    	auto end() -> decltype(adlcheck::adl_begin(t)) { auto ret = adlcheck::adl_begin(t); std::advance(ret, n2); return ret; }
        
        //auto begin() -> decltype(std::begin(t))  { auto ret = std::begin(t); std::advance(ret, n1); return ret; }
        //auto end() -> decltype(std::begin(t)) { auto ret = std::begin(t); std::advance(ret, n2); return ret; }
        
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


namespace kitties
{
    template<typename T>
    struct mycontainer
    {
        std::vector<T> vec;
        
        friend auto begin(mycontainer& c) -> decltype(c.vec.begin()) { cout<<"Meow"<<endl; return c.vec.begin(); }
        friend auto end(mycontainer& c) -> decltype(c.vec.end()) { cout<<"Woof"<<endl; return c.vec.end(); }
    };
}

int main()
{
	cout<<std::boolalpha;

	std::array<int, 5> arr = {{1, 2, 3, 4, 5}};
	std::vector<int> v;
    
    kitties::mycontainer<int> mc;
	for(auto& i: arr)
    {
		v.push_back(i);
        mc.vec.push_back(i);
    }
    
    for(auto const& i: make_range<1, 4>(mc))
        cout<<i<<' ';
        
    cout<<endl;
        
    for(auto const& i: make_range<1, 3>(arr))
        cout<<i<<' ';
        
    cout<<endl;
        
    for(auto& i: make_range<2, 4>(v))
        i = i*2;
        
    for(auto& i: v)
    	cout<<i<<' ';
}