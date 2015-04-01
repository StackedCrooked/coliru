#include <vector>
#include <iostream>
using namespace std;

void display_sizes(const std::vector<int>& nums1,
                   const std::vector<int>& nums2,
                   const std::vector<int>& nums3)
{
    std::cout << "nums1: " << nums1.size() 
              << " nums2: " << nums2.size()
              << " nums3: " << nums3.size() << '\n';
}
 
int main()
{
    std::vector<int> nums1 {3, 1, 4, 6, 5, 9};
    std::vector<int> nums2; 
    std::vector<int> nums3;
 
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
    
    typedef struct
    {
        double Low_Altitude;                            // Low Altitude Value
        double Upper_Altitude;                          // High Altitude Value
    }
    Altitude_Range_t;

    Altitude_Range_t a = {100, 200};
    Altitude_Range_t b = {200, 300};
    Altitude_Range_t c = {300, 400};
    Altitude_Range_t d = {400, 500};
    Altitude_Range_t e = {20, 89};
    
    std::vector<Altitude_Range_t> altitudeRanges;
    altitudeRanges.push_back(b);
    altitudeRanges.push_back(a);
    altitudeRanges.push_back(c);
    altitudeRanges.push_back(d);
    
    std::vector<Altitude_Range_t> m_altitudeRanges;
    
    if (m_altitudeRanges != altitudeRanges)
    {
      cout << "m_altitudeRanges(empty) != altitudeRanges\n";
    }
    
    m_altitudeRanges.push_back(b);
    if (m_altitudeRanges != altitudeRanges)
    {
      cout << "m_altitudeRanges(1 item) != altitudeRanges\n";
    }
        
    m_altitudeRanges = altitudeRanges;
    /*if (m_altitudeRanges == altitudeRanges)
    {
        cout << "m_altitudeRanges == altitudeRanges\n";
    }*/
        
}