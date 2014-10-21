#include <iostream>
#include <iomanip>

int main() {
    double value = 1.2;
    double bucketSize = 0.4;
    double bucketId = value / bucketSize;
    
    std::cout << std::setprecision(64) << "bucketId as double: " << bucketId << std::endl;
    std::cout << "bucketId as int: " << int(bucketId) << std::endl;
}
