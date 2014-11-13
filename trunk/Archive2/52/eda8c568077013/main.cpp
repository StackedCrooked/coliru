#include <iostream>
#include <string>
#include <vector>

#include <chrono>

using namespace std::chrono;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
	{
		os << el << ' ';
	}
	return os;
}

void date_from_days_since_epoch(int64_t g, int32_t& y, int32_t& mm, int32_t& dd)
{
	g += 135080;
	y = (10000 * g + 14780) / 3652425;
	int64_t ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
	if (ddd < 0)
	{
		y = y - 1;
		ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
	}
	int64_t mi = (100 * ddd + 52) / 3060;
	mm = (mi + 2) % 12 + 1;
	y = y + (mi + 2) / 12 + 1600;
	dd = ddd - (mi * 306 + 5) / 10 + 1;
	return;
}

int main()
{
	std::vector<std::string> words = {
		"Hello", "from", "Vova", "to", "Vitalik", "!"
	};
	std::cout << words << std::endl;

	int32_t y, mm, dd;

    int64_t starts[] = { 0, 58, 364 + 59, 729 + 59, 1094 + 59, 1459 + 59, 11015, 15999 };
	int64_t   ends[] = { 2, 61, 367 + 59, 732 + 59, 1097 + 59, 1462 + 59, 11018, 16001 };
	for (uint32_t i = 0; i < sizeof(starts) / sizeof(int64_t); i++)
		for (int64_t g = starts[i]; g < ends[i]; g += 1)
		{
			date_from_days_since_epoch(g, y, mm, dd);
			std::cout << g << ": " << y << "-" << mm << "-" << dd << std::endl;
		}
	std::cout << std::endl;

	high_resolution_clock::time_point time1 = high_resolution_clock::now();
	for (int i = 0; i < 100000000 /*100M*/; i++)
	{
		date_from_days_since_epoch(i, y, mm, dd);
	}
	high_resolution_clock::time_point time2 = high_resolution_clock::now();

	uint64_t time = duration_cast<microseconds>(time2 - time1).count();
	std::cout << "\ndate_from_days_since_epoch: " << time << " microsecond(s) to run\n\n";
}
