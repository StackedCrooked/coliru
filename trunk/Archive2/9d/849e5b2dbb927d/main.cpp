#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

template <class Function>
void fill_vector(std::vector<int> &v, Function side)
{
    for(auto i=v.begin(); i!=v.end(); ++i)
    {
        *i = rand() % 100;
    }
    side(v);
}

int main()
{
    std::vector<int> v(20);
    fill_vector(v,[](std::vector<int>const&){});

    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));

    std::cout << std::endl;

    std::vector<int> v2(20);
    int max;
    fill_vector(v2,[&max](std::vector<int> const& v){ max = *std::max_element(begin(v), end(v)); });
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
    std::cout << max << std::endl;

    return 0;
}