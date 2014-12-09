#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <tuple>
int main()
{
    std::vector<double> data = { 
        1.3, 1.1, 
        2.1, 
        3.4, 3.3, 3.2, 3.1, 
        //4.3, 4.2, 4.1, 
        5.2, 5.1,
        6.1 };
 
    auto comp = [](double lhs, double rhs) { return static_cast<int>(lhs) < static_cast<int>(rhs); };
    auto lower = std::lower_bound(data.begin(), data.end(), 4.999, comp);
    auto upper = std::upper_bound(data.begin(), data.end(), 4.001, comp);
    
    std::cout << "lower - begin : "  << std::distance(data.begin(), lower) << std::endl;
    std::cout << "upper - begin : "  << std::distance(data.begin(), upper) << std::endl;
    if (lower != data.end())
        std::cout << "*lower : " << *lower << std::endl;
    if (upper != data.end())    
        std::cout << "*upper : " << *lower << std::endl;
    
    std::copy(lower, upper, std::ostream_iterator<double>(std::cout, ", "));    
}

// output
// 4.3, 4.2, 4.1, 