#include <iostream>
#include <tuple>
using namespace std;

template <typename T>
T random_num() {
    return 0;
}

template<>
int random_num<int>() {
  return 4;   
}

template<>
float random_num<float>() {
  return 4.2f;
}

// The idea is to build tuples recursively where the types are fixed at compile time
// and the data is loaded dynamically (e.g. the random_num functions).
// So one could write
// auto res = construct<float, int>();
// where res is std::tuple<float, int> with values (4.2f, 4)
template <size_t idx, typename Tup, typename... Args>
struct Builder;

// Append a dynamically generated value to the tuple
template <size_t idx, typename Tup, typename First, typename... Args>
struct Builder<idx, Tup, First, Args...>
{
    static auto construct(Tup t) 
        //-> decltype(std::tuple_cat(t, std::make_tuple()) // I guess this is the culprit
    {
        First n = random_num<First>(); // Get the numbers dynamically, with the types given in the parameter pack
        auto next_arg_pack = std::tuple_cat(t, std::make_tuple(n));
        std::cout << idx << "\n";
        return Builder<idx + 1, decltype(next_arg_pack), Args...>::construct(next_arg_pack);
    }
};

template <size_t idx, typename Tup>
struct Builder<idx, Tup>
{
    static Tup construct(Tup args)
    {
        return args;
    }
};

template <typename... Args>
auto construct() {
    return Builder<2, std::tuple<>, Args...>::construct(std::make_tuple());
}

int main() {
    
	// Should be std::tuple<int, float>, (4, 4.2f, 4)
	auto tup = construct<int, float, int>();
    std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << "\n";
	return 0;
}