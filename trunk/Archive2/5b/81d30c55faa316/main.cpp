#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <future>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <limits>
#include <functional>

template<typename C, typename Key, typename Pred = std::equal_to<typename C::iterator::value_type>>
struct Find_all {
    using Iter = typename C::const_iterator;

	std::vector<uint32_t> operator()(const C& v, const Key key)
	{
		Iter it = v.cbegin();
		std::vector<uint32_t> vr;

		while (it != v.end())
		{
			it = std::find(it, v.cend(), key);

			if (it != v.cend())
			{
				vr.push_back(std::distance(v.cbegin(), it));
				it++;
			}
		}

		return vr;
	}
};

template<typename C, typename Key>
class IngenuousParallelFind {

public:
	std::vector<uint32_t> operator()(C& c, Key key)
	{
		using Iter = typename C::iterator;

		unsigned int qty_threads = std::thread::hardware_concurrency();
		unsigned int slice = c.size() / qty_threads;

		std::vector<C> v;

		for (int i = 0; i < qty_threads - 1; ++i)
		{
			v.push_back(std::move(C{ c.begin() + i * slice, c.begin() + (i + 1) * slice }));
		}

		v.push_back(std::move(C{ c.begin() + (qty_threads - 1) * slice, c.end() }));

		using Find = Find_all<C, Key>;
		using Result = std::vector<uint32_t>;

		std::vector<std::future<Result>> v_future;

		for (int i = 0; i < qty_threads; ++i)
		{
			std::future<std::vector<uint32_t>> f = std::async(std::launch::async, Find{}, std::move(v.at(i)), key);
			//f.wait_for(std::chrono::milliseconds(200));
			v_future.push_back(std::move(f));
		}

		std::vector<uint32_t> result;

		for (int i = 0; i < v_future.size(); ++i)
		{
			int offset = i * slice;

			std::vector<uint32_t> tmp = v_future.at(i).get();

			for (int j = 0; j < tmp.size(); ++j)
			{
				result.push_back(offset + tmp.at(j));
			}
		}

		return result;
	}
};

class Random_int final {
	using Param_type = typename std::uniform_int_distribution<>::param_type;
	std::default_random_engine dre;
	std::uniform_int_distribution<> uid;
	unsigned long seed;
	std::function<int()> f;

public:
	Random_int(const int32_t a = std::numeric_limits<int32_t>::min(),
		const int32_t b = std::numeric_limits<int32_t>::max())
		: Random_int{ a, b, generate_seed() } {}

	Random_int(const int32_t a, const  int32_t b, const  unsigned long seed)
	{
		set_seed(seed);
		uid.param(Param_type{ a, b });
		f = std::bind(uid, dre);
	}

	int operator()();
	void set_seed(unsigned long seed) noexcept;
	unsigned long generate_seed() const;
	unsigned long get_seed() const noexcept{ return seed; }
};

int Random_int::operator()()
{
	return f();
}

void Random_int::set_seed(unsigned long seed) noexcept
{
	this->seed = seed;
	dre.seed(this->seed);
}

unsigned long Random_int::generate_seed() const
{
	return static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count());
}

struct Record {
	int id;
	std::string name;

	bool operator==(const Record& r) const { return id == r.id && name == r.name; }
};

void run_find_parallel(Random_int r, int total)
{
	std::vector<Record> v;

	for (int i = 0; i < total; ++i)
	{
		int n = r();
		v.push_back(Record{ n, std::to_string(n) });
	}

	int key = r();
	Record rec{ key, std::to_string(key) };

	std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();

	IngenuousParallelFind<std::vector<Record>, Record> ipf;

	std::vector<uint32_t> result = ipf(v, rec);

	std::chrono::steady_clock::time_point tp2 = std::chrono::steady_clock::now();

	std::chrono::steady_clock::duration d = tp2 - tp1;

	std::cout << "Duração: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(d).count()
		<< " millisegundos."
		<< std::endl;

	std::cout << key << " foi encontrado " << result.size() << " vezes." << std::endl;

	if (result.size() < 30)
		std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl;
}

void run_find_sequential(Random_int r, int total)
{
	std::vector<Record> v;

	for (int i = 0; i < total; ++i)
	{
		int n = r();
		v.push_back(Record{ n, std::to_string(n) });
	}

	int key = r();
	Record rec{ key, std::to_string(key) };

	std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();

	Find_all<std::vector<Record>, Record> fa;

	std::vector<uint32_t> result = fa(v, rec);

	std::chrono::steady_clock::time_point tp2 = std::chrono::steady_clock::now();

	std::chrono::steady_clock::duration d = tp2 - tp1;

	std::cout << "Duração: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(d).count()
		<< " millisegundos."
		<< std::endl;

	std::cout << key << " foi encontrado " << result.size() << " vezes." << std::endl;

	if (result.size() < 30)
		std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl;
}

void test_random_int()
{
	Random_int r{};
	//    Random_int r { 0 };
	//    Random_int r {0, 50};
	//    Random_int r {-100, 0 };
	//    Random_int r {0, 50, 100};

	for (int i = 0; i < 10; ++i)
		std::cout << r() << std::endl;
}
int main(int argc, char** argv) {
	Random_int r{ 0, 1000000 };
	int total = 5000000;

	std::cout << "Parallel..." << std::endl;
	std::async(std::launch::async, [](Random_int r, int total){ run_find_parallel(r, total); }, r, total);

	std::cout << "Sequential..." << std::endl;
	std::async(std::launch::async, [](Random_int r, int total){ run_find_sequential(r, total); }, r, total);
	//test_random_int();

	return 0;
}