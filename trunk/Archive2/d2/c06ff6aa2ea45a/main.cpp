#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>

struct coin {
    char output;
    unsigned char value;    
    bool operator>(const coin& rhs) const {return value>rhs.value;}
};

void solve(std::vector<std::string>& results, std::string& currSoln, unsigned target, const std::vector<coin>& coins, unsigned coinnumber)
{
    coin curcoin = coins[coinnumber];
    unsigned max = target/curcoin.value;
    if (coinnumber < coins.size()-1) {
        solve(results,currSoln,target,coins,coinnumber+1);
        unsigned prevlen = currSoln.size();
        for(unsigned i=1; i<=max; ++i) 
        {
            currSoln.push_back(curcoin.output);
            solve(results,currSoln,target-i*curcoin.value,coins,coinnumber+1);
        }
        currSoln.erase(prevlen);
    } else if (curcoin.value*max == target) {
        std::string newresult;
        newresult.reserve(currSoln.size() + max);
        newresult = currSoln;
        newresult.append(max, curcoin.output);
        results.emplace_back(std::move(newresult));
    }
}
std::vector<std::string> solve(unsigned target, const std::vector<coin>& coins)
{
    std::vector<coin> sortedcoins = coins;
    std::sort(sortedcoins.begin(), sortedcoins.end(), std::greater<coin>());
    std::vector<std::string> results;
    results.reserve(target*target/2);
    std::string currSoln;
    currSoln.reserve(target/2);
    solve(results, currSoln, target, sortedcoins, 0);
    return results;
}

int main() {
    std::vector<coin> coins = {{'p',1}, {'n',5}, {'d',10}, {'q',25}};
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> results = solve(100, coins);
    auto stop = std::chrono::high_resolution_clock::now();
    for(const std::string& result : results) 
        std::cout << result << '\n';
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    std::cout << "found " << results.size() << " solutions\n";
    std::cout << "took " << dur.count() << "ns\n";
    return 0;
}