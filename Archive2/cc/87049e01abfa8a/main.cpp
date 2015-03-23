//http://stackoverflow.com/questions/29215916/perform-a-random-for-loop-and-save-the-random-values-each-time/29219488?noredirect=1#comment46652632_29219488
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

unsigned GetRandomNumber(unsigned nLow, unsigned nHigh, const std::vector<unsigned>& ignored)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(nLow, nHigh-ignored.size());
    unsigned value = dis(gen);
    auto it = std::upper_bound(ignored.begin(), ignored.end(), value);
    value += it-ignored.begin();
    while(it != ignored.end() && *it<= value) {
        ++it;
        ++value;
    }
    return value;
}

int main() {
    std::vector<unsigned> ignored;
    ignored.push_back(2);
    ignored.push_back(4);
    ignored.push_back(6);
    char dist[6] = {};
    for(int i=0; i<255; ++i) {
        unsigned v = GetRandomNumber(1,6,ignored);
        dist[v]++;
        std::cout << v;
    }
    for(int i=0; i<6; ++i)
        std::cout << '\n' << +dist[i];
    return 0;
}