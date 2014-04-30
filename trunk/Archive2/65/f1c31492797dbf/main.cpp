#include <array>
#include <iostream>

using namespace std;

class type_id_t
{
    using sig = type_id_t();

	sig* id;
	type_id_t(sig* id) : id{id} {}

public:
	template <typename T>
	friend type_id_t type_id();

	bool operator==(type_id_t o) const { return id == o.id; }
	bool operator!=(type_id_t o) const { return id != o.id; }
};

template <typename T>
type_id_t type_id() { return &type_id <T>; }

template<typename... T>
std::array<type_id_t, sizeof...(T)>
make_ids()
{
	return std::array<type_id_t, sizeof...(T)>{{type_id<T>()...}};
}

template<size_t N> struct size {};

template<typename T, size_t N, size_t I>
void comp_ids_impl(const std::array<type_id_t, N>& a, size<I>)
{
	std::cout << (type_id<T>() == a[I]) << " ";
	comp_ids_impl<T>(a, size<I + 1>{});
}

template<typename T, size_t N>
void comp_ids_impl(const std::array<type_id_t, N>& a, size<N>)
{
	std::cout << std::endl;
}

template<typename T, typename A>
void comp_ids(const A& a) { comp_ids_impl<T>(a, size<0>{}); }

int main ()
{
    auto ids = make_ids<
		int, bool, double const&, int&&, char(&)[8],
		int, void(int), unsigned char**, std:array<void(*)(), 35>, double[4][8]
	>();

	comp_ids<int>(ids);  // output: 1 0 0 0 0 1 0 0 0 0
}
