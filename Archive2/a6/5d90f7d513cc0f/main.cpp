#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class iterator>
void move_to_front(iterator movethis, iterator leftend) {
    std::rotate(leftend, movethis, movethis + 1);
}

int main()
{
    std::vector<int> v{1,2,3,4,5};
    
    move_to_front(v.begin() + 3, v.begin());
    
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";
}