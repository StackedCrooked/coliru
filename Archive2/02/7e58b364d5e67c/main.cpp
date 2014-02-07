#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <regex>

template<typename Floating>
std::string formatFloatingUpToN(unsigned n, Floating f) {
    std::stringstream out;
    out << std::setprecision(n) << std::fixed;
    out << f;
    
    std::string ret = out.str();
    
    // if this clause holds, it's all zeroes
    if (std::abs(f) < std::pow(0.1, n))
        return ret;
    
    while (true) {
        if (ret.back() == '0') {
            ret.pop_back();
            continue;
        } else if (ret.back() == '.') {
            ret.pop_back();
            break;
        } else
            break;
    }
        
    return ret;
}

int main() {
    //special cases
    std::cout << formatFloatingUpToN(3, 100.0 * 9.505) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 9.5) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * -0.9505) << '%' << '\n';
    std::cout << '\n';
    
    // regular cases
    std::cout << formatFloatingUpToN(3, 100.0 * 0.95) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.095) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.0095) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.00095) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.000095) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.0000095) << '%' << '\n';
    std::cout << formatFloatingUpToN(3, 100.0 * 0.00000095) << '%' << '\n';
}