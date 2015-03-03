#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::vector<float> gauss(std::size_t len, float sigma) {
    const double pi = std::acos(-1);
    std::cout << "pi: " << pi << std::endl;
    std::vector<float> result;
    result.resize(len);
    
    auto sigmasq = sigma*sigma;
    for(std::size_t x = 0; x < result.size(); ++x) {
        result[x] = std::exp(-x*x / (2*sigmasq)) / std::sqrt(2*pi*sigmasq);
    }
    
    return result;
}

int main() {
    auto gauss_vals = gauss(4, 0.84089642f);
    for(auto val : gauss_vals) {
        std::cout << val << " ";
    }
}
