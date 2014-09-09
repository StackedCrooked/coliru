#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

int main()
{
    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int b[10], c[10];
    auto p = std::partition_copy(std::begin(a), std::end(a),
                                 std::begin(b), std::begin(c),
                                 std::bind2nd(std::modulus<int>(), 2));
                                 
    std::copy(std::begin(b), p.first,
                             std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
                            
    std::copy(std::begin(c), p.second,
                             std::ostream_iterator<int>(std::cout, " "));
}
