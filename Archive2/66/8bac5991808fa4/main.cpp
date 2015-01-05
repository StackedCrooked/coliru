#include <algorithm>
#include <iostream>
#include <vector>

std::pair<int, int> find_equal_sum(const std::vector<int>& arr,const int x)
{
    int max = arr[arr.size()-1];//O(1)
	std::vector<int> direct_index_hash(max+1, 0);//O(n)
	for (size_t i = 0; i < arr.size(); i++)//O(n)
		direct_index_hash[arr[i]] ++;
	for (size_t i = 0; i < arr.size(); i++)//O(n)
	{
		int diff = x - arr[i];
		if (diff <0) 
			continue;
		int diff_count = direct_index_hash[diff];
		if (diff == arr[i]){
			diff_count--;
		}
		if (diff_count >0)
			return std::make_pair(arr[i], diff);
	}
	return std::make_pair(-1, -1);
}
int main()
{
	const int x = 10;
	std::vector<int> arr{ 1, 5, 9, 14 };
	auto res=find_equal_sum(arr, x);
	std::cout << res.first <<" "<< res.second;
	return 0;
}