#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

template <typename T, typename A, typename U>
std::vector<T, A>& operator+=(std::vector<T, A>& v, std::initializer_list<U> il)
{
    std::copy(std::begin(il), std::end(il), std::back_inserter(v));
    return v;
}

int main()
{
	std::vector<int> values;
	values += {3, 9, 2, 5, 8};
    
    for (int i : values)
    {
        std::cout << i << " ";
    }
}
