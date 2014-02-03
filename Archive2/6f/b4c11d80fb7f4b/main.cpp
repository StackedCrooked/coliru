#include <iostream>
#include <array>
using namespace std;

//initializes a std::array in a constructor
//works with Clang 3.4, not working in GCC 4.8
template <std::size_t N>
struct const_string { 
  std::array<char, N> x; 
  //A():x{1,2,3,4} { } 
  const_string (std::array<char, N> arr):x(arr) { } 
  
};



template <char... STR>
constexpr const_string<sizeof...(STR)> operator"" _cstr()
{
  return const_string<sizeof...(STR)>(STR...);
}

template<size_t... Sizes>
constexpr std::size_t test(const char (&...args)[Sizes]) 
{
    return sizeof...(Sizes);
}

template <typename T>
std::size_t test2(std::initializer_list<T> var) 
{
    for (auto s : var)
        cout << s.x << '\n';
}

int main() {
    //A a ({'b','u','g'});
    cout << test("test", "nest") << '\n';
    cout << test2({const_string<5>({"test"}), const_string<5>({"est"})}) << '\n';
	const_string<4> a ({"bug"});
    const_string<5> b ({"bugs"});
	for (int i = 0; i < 4; ++i)
		cout << b.x[i] << '\n';
	// your code goes here
	return 0;
}