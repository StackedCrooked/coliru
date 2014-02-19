#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    const int r[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::vector<int> v1(std::begin(r), std::end(r));
    std::vector<int> v2(v1.rbegin(), v1.rend());
    
    auto ostreamOutFunc = std::mem_fn<std::ostream&(int)>(&std::ostream::operator<<);
    auto coutInt = std::bind(ostreamOutFunc, &std::cout, std::placeholders::_1);
	std::for_each(std::begin(v1), std::end(v1), coutInt);
    
    std::cout.flush();
}
