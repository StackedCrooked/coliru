#include <atomic>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

int main()
{
    double sum=0;
    auto it = M.begin<double>(), it_end = M.end<double>();
    vector<float> foo;
    for(auto it = M.begin<float>() ; it != M.end<float>(); ++it) {
        foo.push_back(*it);
    }
}