#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> gauss(std::size_t len, double sigma) {
    const double pi = std::acos(-1);
    std::vector<double> result;
    result.resize(len);
    
    auto sigmasq = sigma*sigma;
    for(std::size_t x = 0; x < result.size(); ++x) {
        double xsq = std::pow(static_cast<double>(x), 2);
        result[x] = 1.0f / std::sqrt(2*pi*sigmasq) * std::exp(-xsq / (2.0f*sigmasq));
    }
    
    return result;
}

int main() {
    auto gauss_vals = gauss(4, 0.84089642);
    for(auto val : gauss_vals) {
        std::cout << val << " ";
    }
}
