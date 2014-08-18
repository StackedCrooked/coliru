#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

int main() {
    std::vector<double> vd{1.0, 1.1, 1.2, 1.3};
    std::vector<std::string> vs;
    std::transform(vd.begin(), vd.end(), std::back_inserter(vs), [](double d){ return std::to_string(d); });
    
    for(auto const& s : vs) std::cout << s << " ";
}