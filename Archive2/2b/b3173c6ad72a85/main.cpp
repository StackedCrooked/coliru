#include <iostream>
#include <vector>
#include <algorithm>

struct Play{
    int min, down, yard, locat;
    std::string Description, offname, defname;
    double relevance;
    };

    bool customCompare(const Play &x, const Play &y)
    {
        return (x.relevance < y.relevance);
    }

    void printResults(std::vector<Play>& vecData)
    {
        std::sort(vecData.begin(),vecData.end(), customCompare);
    }

int main() { 
    std::vector<Play> vec;
    vec.push_back({0,0,0,0,
    "desc", "offname", "defname",
    42});
    vec.push_back({0,0,0,0,
    "desc", "offname", "defname",
    12});
    for (const auto& v : vec) {
        std::cout << v.relevance << std::endl;
    }
    printResults(vec);
    for (const auto& v : vec) {
        std::cout << v.relevance << std::endl;
    }
    return 0;
}