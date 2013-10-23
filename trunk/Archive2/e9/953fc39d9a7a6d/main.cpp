#include <functional>
#include <iostream>
#include <type_traits>
#include <utility> 

struct equal_to {
    template<typename T, typename T2>
    bool operator()(T &&t, T2 &&t2) {
        return helper_<T, T2>(0, std::forward<T>(t), std::forward<T2>(t2));   
    }
    
private:
    template<typename T, typename T2>
    auto helper_(int, T &&t, T2 &&t2) -> decltype(void(t == t2), bool{}) {
        return t == t2;
    }
    
    template<typename T, typename T2>
    auto helper_(long, T &&t, T2 &&t2) {
        return t2 == t;
    }
};

template<bool OneTrue, typename F>
struct AllTrue {
    template<typename T>
    bool operator()(T &&) {
        return OneTrue;
    }
    
    template<typename Head, typename Head2, typename... Tail>
    bool operator()(Head &&head, Head2 &&head2, Tail&&... tail) {
        return F()(head, head2) && (*this)(std::forward<Tail>(tail)...);
    }
};

AllTrue<true, equal_to> all_equal;

struct S {};

bool operator==(S, int) {return true;}

int main()
{
	std::cout << all_equal(4, S(), 4) << '\n';
//	std::cout << (increasing % 1/10/100) << '\n';
//	std::cout << (decreasing % 1/-10/-100) << '\n';
//	std::cout << (strictly_increasing % 1/1/2/3/60) << '\n';
//	std::cout << (strictly_decreasing % 3/2/1) << '\n';
}