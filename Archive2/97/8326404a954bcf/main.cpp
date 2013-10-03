#include <array>
#include <iostream>

template<class T, std::size_t N>
struct non_aggr
{
private:
    T arr[N];
public:
	template<class... TT>
	non_aggr(TT&&... pp)
	: arr{std::forward<TT>(pp)...}
	{}
	
	T* begin() { return arr; }
	T* end() { return arr+N; }
};

int main()
{
	std::array<int, 10> aggr_obj = {10,3,1,4,5,6,2,9,8,7};
	for(auto const& e : aggr_obj) std::cout << e << ", ";
	std::cout << std::endl;
	
	//non_aggr<int, 10> non_aggr_obj = {10,3,1,4,5,6,2,9,8,7};
	//for(auto const& e : non_aggr_obj) std::cout << e << ", ";
	//std::cout << std::endl;
}