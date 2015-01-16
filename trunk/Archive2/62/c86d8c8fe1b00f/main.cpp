#include <forward_list>
#include <iostream>
 
void display_sizes(const std::forward_list<int> &nums1,
                   const std::forward_list<int> &nums2,
                   const std::forward_list<int> &nums3)
{
    std::cout << "nums1: " << std::distance(nums1.begin(), nums1.end()) 
              << " nums2: " << std::distance(nums2.begin(), nums2.end())
              << " nums3: " << std::distance(nums3.begin(), nums3.end()) << '\n';
}
 
int main()
{
    std::forward_list<int> nums1 {3, 1, 4, 6, 5, 9};
    std::forward_list<int> nums2; 
    std::forward_list<int> nums3;
 
    std::cout << "Initially:\n";
    display_sizes(nums1, nums2, nums3);
 
    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;
 
    std::cout << "After assigment:\n"; 
    display_sizes(nums1, nums2, nums3);
 
    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);
 
    std::cout << "After move assigment:\n"; 
    display_sizes(nums1, nums2, nums3);
}