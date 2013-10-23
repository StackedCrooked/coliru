#include <iostream>
#include <utility> 

template<typename T>
bool all_equal(T &&) {
    return true;
}

template<typename Head, typename Head2, typename... Tail>
bool all_equal(Head &&head, Head2 &&head2, Tail&&... tail) {
    return head == head2 && all_equal(std::forward<Tail>(tail)...);
}

int main()
{
	std::cout << (all_equal(4, 4, 4)) << '\n';
//	std::cout << (increasing % 1/10/100) << '\n';
//	std::cout << (decreasing % 1/-10/-100) << '\n';
//	std::cout << (strictly_increasing % 1/1/2/3/60) << '\n';
//	std::cout << (strictly_decreasing % 3/2/1) << '\n';
}