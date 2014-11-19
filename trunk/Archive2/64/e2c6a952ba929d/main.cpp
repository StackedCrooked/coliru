#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
 
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> v;
    generate_n(back_inserter(v), 20, bind(dist, gen));
 
    std::cout << "Before sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
 
    selection_sort(v.begin(), v.end());
 
    std::cout << "\nAfter sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}