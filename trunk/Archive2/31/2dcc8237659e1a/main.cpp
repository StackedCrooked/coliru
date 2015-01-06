#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <future>
#include <thread>
#include <type_traits>
#include <vector>

template <typename Iterator>
auto do_square(Iterator begin, Iterator end)
{
    using value_type = decltype(*begin);
	auto fut = std::async([&begin, &end]() -> Iterator
		{
			return std::transform(begin, end, begin, 
				[](value_type a)
				{
					return a * a;
				});
		});
    return fut;
}

template <typename Iterator1, typename Iterator2, typename OutputIt>
OutputIt do_merge(Iterator1 begin1, Iterator1 end1,
              Iterator2 begin2, Iterator2 end2,
              OutputIt out)
{
    while(begin1 != end1 || begin2 != end2) {
        if(*begin1 < *begin2) {
            *out = *begin1;
            ++begin1;
        } else {
            *out = *begin2;
            ++begin2;
        }
    }
    
    while(begin1 != end1) {
        *out = *begin1;
        ++begin1;
    }
    while(begin2 != end2) {
        *out = *begin2;
        ++begin2;
    }
    return out;
}

template <typename Iterator>
auto sort_and_square(Iterator begin, Iterator end)
{
	using ra_iter = std::random_access_iterator_tag;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
	using iter_type = typename std::iterator_traits<Iterator>::iterator_category;
	static_assert(std::is_base_of<ra_iter, iter_type>::value,
				  "Assumes a Random Access Iterator");
                  
    auto mid = std::find_if(begin, end, [](const value_type& a) 
        { return a > value_type{}; });
	auto fut = do_square(begin, mid);
	auto fut2 = do_square(mid, end);
	auto neg = fut.get();
	auto pos = fut2.get();

    for(auto it = std::reverse_iterator<Iterator>(neg + 1); 
             it != std::reverse_iterator<Iterator>(begin);
             ++it)
    {
        std::cout << *it << "\n";
    }
    
    std::vector<value_type> v(std::distance(begin, end));
    do_merge(std::reverse_iterator<Iterator>(neg + 1),
               std::reverse_iterator<Iterator>(begin),
               mid, pos, std::begin(v));
    return v;
}
	
int main()
{
	std::vector<int> v{-10,-9,-5,-2,1,2,3,4,5};
	sort_and_square(std::begin(v), std::end(v));
	for(int i : v) {
		std::cout << i << ", ";
	}
	std::cout << "\n";
}
	
	