#include <functional>
#include <iostream>
#include <utility> 

template<bool OneTrue, template<typename> class F>
struct AllTrue {
    template<typename T>
    bool operator()(T &&) {
        return OneTrue;
    }
    
    template<typename Head, typename Head2, typename... Tail>
    bool operator()(Head &&head, Head2 &&head2, Tail&&... tail) {
        return F<Head>()(head, head2) && (*this)(std::forward<Tail>(tail)...);
    }
};

AllTrue<true, std::equal_to> all_equal;

int main()
{
	std::cout << (all_equal(4, 4, 4)) << '\n';
//	std::cout << (increasing % 1/10/100) << '\n';
//	std::cout << (decreasing % 1/-10/-100) << '\n';
//	std::cout << (strictly_increasing % 1/1/2/3/60) << '\n';
//	std::cout << (strictly_decreasing % 3/2/1) << '\n';
}