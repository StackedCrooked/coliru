#include<vector>
#include<list>
#include<algorithm>
#include<iostream>
#include<iterator>
#include<functional>

int main() 
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {2, 5, 4};
    std::list<int> res;
    std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(res), std::plus<int>());
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, ","));
}