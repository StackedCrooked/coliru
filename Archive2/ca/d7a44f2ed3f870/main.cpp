#include <vector>
#include <algorithm>
#include <iostream>

std::vector<std::vector<int>> minPartition (std::vector<int>& in) {
    std::vector<std::vector<int>> partitions(1);  // At least one empty partition
    if (in.size() == 0)
        return partitions;
    std::sort(in.begin(), in.end());
    auto old = in.front();
    for(std::size_t i = 0, currPart = 0; i < in.size(); ++i, ++currPart) {
        if(in[i] != old) {
            old = in[i];
            currPart = 0;
        }
        if (currPart == partitions.size() )
            partitions.resize(currPart + 1);
        partitions[currPart].push_back(in[i]);
    }
    return partitions;
}

int main () {
    std::vector<int> test{-1,4,5,4,-1,-1};
    auto partitions = minPartition(test);
    
    for (const auto& part : partitions) {
        for (const auto& v : part)
            std::cout << v << " ";
        std::cout << "\n";
    }
}
    