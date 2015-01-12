#include <algorithm>
#include <iostream>
#include <vector>

std::pair<int, int> find_equal_sum(const std::vector<int>& arr, const int x)
{
    if (arr.size()>1){
		int first = 0;
		int last = arr.size() - 1;
		while (true){
			if (arr[first] + arr[last]>x)
				--last;
			else if (arr[first] + arr[last]<x)
				++first;
			else if (arr[first] + arr[last] == x){
				return std::make_pair(arr[first], arr[last]);
				break;
			}

		}
	}
	return std::make_pair(-1, -1);//does not exist
}
int main()
{
	const int x = 19;
	std::vector<int> arr{ 5, 7, 8, 11, 12 };
	auto res = find_equal_sum(arr, x);
	std::cout << res.first << " " << res.second;
	return 0;
}