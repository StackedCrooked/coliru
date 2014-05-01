#include <vector>
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
std::vector<type_id_t>
make_ids() { return {type_id<T>()...}; }

template<typename T, typename A>
void comp_ids(const A& a)
{
    for (auto i : a)
		std::cout << (type_id<T>() == i) << " ";
	std::cout << std::endl;
}

int main ()
{
	auto ids = make_ids<
		int, bool, double const&, int&&, char(&)[8],
		int, void(int), unsigned char**, std::vector<void(*)()>, double[4][8]
	>();

	comp_ids<int>(ids);  // output: 1 0 0 0 0 1 0 0 0 0
}
