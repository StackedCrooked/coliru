#include <algorithm>
#include <iostream>
#include <iterator>

template <typename T, std::size_t N>
std::reverse_iterator<T*> rbegin(T (&a)[N])
{
    return std::reverse_iterator<T*>{std::end(a)};
}

template <typename T, std::size_t N>
std::reverse_iterator<T*> rend(T (&a)[N])
{
    return std::reverse_iterator<T*>{std::begin(a)};
}


int main()
{
    const int arrayOfValues[] = {3,1,3,4,4,3,2};
	const int index =
		std::distance(std::begin(arrayOfValues),
			std::max_element(rbegin(arrayOfValues),
							 rend(arrayOfValues)).base() - 1);
	std::cout << index;
}
