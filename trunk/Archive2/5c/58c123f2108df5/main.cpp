#include <array>

template<typename T, size_t N>
struct static_array
{
    T elems[N];
};

int main() {
	std::array<int, 3> a = {1,2,3};
	static_array<int, 3> b = {1,2,3};
	return 0;
}