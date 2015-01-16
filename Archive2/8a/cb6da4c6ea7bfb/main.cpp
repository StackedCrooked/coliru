#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    std::string S{"abcde"};
    std::vector<long long> init{0};
    const long long p = 27;
    const long long q = 10000007;

    auto prefixHash = std::accumulate(S.begin(), S.end(), init, 
    [](std::vector<long long> &acc, char c) {
            acc.push_back( (acc.back()*p + c) % q);
            return acc;
        }
    );


    for (auto el : prefixHash) {
        cout << el << endl;
    }
}
