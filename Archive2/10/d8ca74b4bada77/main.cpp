#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
 
struct Sum {
    Sum() { sum = 0; }
    void operator()(int n) { sum += n; }
 
    int sum;
};
 
int main()
{
    vector<int> nums{432,17,89,1,4,456};
 
    cout << "до: ";
    for (auto n : nums) {
        cout << n << " ";
    }
  cout << '\n';
 
   for_each(nums.begin(), nums.end(), [](int &n){ n++; });
    Sum s = for_each(nums.begin(), nums.end(), Sum());
 
   cout << "после:  ";
    for (auto n : nums) {
        std::cout << n << " ";
    }
    cout << '\n';
    cout << "сумма: " << s.sum << '\n';
}