#include <algorithm>// transform
#include <iostream> // cout
#include <iterator> // back_inserter
#include <vector>   // vector
#include <utility>  // pair, make_pair

int main()
{
    // your Halton generator here
    auto const h2 = std::vector<double> { double(1)/2, double(1)/4, double(3)/4, double(1)/8, double(5)/8, double(3)/8, double(7)/8, double(1)/16, double(9)/16 };
    auto const h3 = std::vector<double> { double(1)/3, double(2)/3, double(1)/9, double(4)/9, double(7)/9, double(2)/9, double(5)/9, double(8)/ 9, double(1)/27 };
    std::vector< std::pair<double, double> > h23;
    
    std::transform(begin(h2), end(h2), begin(h3), std::back_inserter(h23), [](double L, double R){ return std::make_pair(L, R); });
    
    for (auto const& p: h23)
        std::cout << "{ " << p.first << ", " << p.second << " }, ";
}