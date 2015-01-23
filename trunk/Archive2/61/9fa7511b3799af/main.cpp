#include <iostream>

// https://twitter.com/SeanParent/status/558330478541803522
template <class F, class... Args>
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

int main() {
    for_each_argument([](auto a){
		std::cout<<a<<std::endl;
	}
	,42,33,11,"bla",'!',"blup");
}
