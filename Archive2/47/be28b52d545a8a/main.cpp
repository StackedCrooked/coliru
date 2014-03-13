#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
 
int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    const int N = 6;
    int nums[N] = {3, 1, 4, 1, 5, 9};
 
    const int min_sorted_size = 4;
    int sorted_size = 0;
    do {
        std::random_shuffle(nums, nums + N, g);
        int *sorted_end = std::is_sorted_until(nums, nums + N);
        sorted_size = std::distance(nums, sorted_end);
 
        for (auto i : nums) std::cout << i << ' ';
        std::cout << " : " << sorted_size << " initial sorted elements\n";
    } while (sorted_size < min_sorted_size);
}