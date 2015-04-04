#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    int data[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    std::vector<int> v(data, data+10);
 
    int num_items1 = std::count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0;});
 
    std::cout << "количество чисел, делящихся на три: " << num_items1 << '\n';
}