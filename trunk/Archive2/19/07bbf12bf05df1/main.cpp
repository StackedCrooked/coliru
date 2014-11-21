#include <iostream>
#include <array>

template <int M, int ...N>
struct multiply_ {
    enum { value = M * multiply_<N...>::value };
};

template <int N>
struct multiply_<N> {
	enum { value = N };
};

template <int ...N>
constexpr int multiply = multiply_<N...>::value;

template <typename T, int ...N>
struct multiarray {
	std::array<T, multiply<N...>> data;
};


// functions working on it (you can make them member 
// functions if you like, but I dislike member 
// functions on principle)
// e.g.
template <typename T, int ...N>
T& front(multiarray<T, N...> ma)
{
    return ma.data[0];
}

template <typename T, int ...N>
T& back(multiarray<T, N...> ma)
{
    return ma.data[multiply<N...>-1];
}

int main() {
	multiarray<float, 3, 5, 2> arr;
    for (int i = 0; i < multiply<3, 5, 2>; i++) {
        arr.data[i] = i;
    }
    
    std::cout << front(arr) << ' ' << back(arr) << std::endl;
    
	return 0;
}