#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    int data[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    std::vector<int> v(data, data+10);
 
    int target1 = 3;
    int target2 = 5;
    int num_items1 = std::count(v.begin(), v.end(), target1);
    int num_items2 = std::count(v.begin(), v.end(), target2);
 
    std::cout << "число: " << target1 << " количество: " << num_items1 << '\n';
    std::cout << "число: " << target2 << " количество: " << num_items2 << '\n';
}