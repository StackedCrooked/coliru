#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>


int main()
{
    std::vector<int> original {1, 6, 2, 8, 4, 8, 3, 7, 2, 3};
    std::vector<int> result;
    std::nth_element(original.begin(), original.begin() + 4, original.end(),
                     [](int l, int r){ return r < l; });
    result.assign(original.begin(), original.begin() + 5);
    for(auto i: result)
        std::cout << i << ' ';
}
