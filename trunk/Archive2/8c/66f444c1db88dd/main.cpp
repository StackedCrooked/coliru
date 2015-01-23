#include <iostream>

// https://twitter.com/SeanParent/status/558330478541803522
template <class F, class... Args>
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

template<typename T1,typename T2>
auto sum_whatever(T1 const& p1,T2 const& p2) {
    return p1+p2;
}

int main() {
    for_each_argument([](auto a){
		std::cout<<a<<std::endl;
	}
	,42,33,11,"bla",'!',"blup");
    
    std::cout<<sum_whatever(1u,2)<<std::endl;
}
