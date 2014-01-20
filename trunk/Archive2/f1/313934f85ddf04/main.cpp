#include <algorithm>
#include <array>
#include <iostream>
#include <iterator> 
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    constexpr int MAX = 14;
    constexpr int LINES = 5;
    
    int sum{};
    int maxNum = 6;
    int minNum{};
    
    std::array<int, LINES> nums;
    
    for (int i = 0; i < LINES; ++i) {
        maxNum = std::min(maxNum, MAX - sum);
        minNum = std::min(maxNum, std::max(minNum, MAX - maxNum * (LINES - i)));
        
        std::uniform_int_distribution<> dist(minNum, maxNum);
        int num = dist(gen);
        
        nums[i] = num;
        sum += num;
    }
    
    std::shuffle(std::begin(nums), std::end(nums), gen);
    std::copy(std::begin(nums), std::end(nums), std::ostream_iterator<int>(std::cout, " "));
}