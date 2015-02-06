#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main()
{
    vector<pair<vector<unsigned>,vector<unsigned> >> a = {{{1,3},{67, 90}}, {{1,2,4},{89,29}}};
    sort(begin(a), end(a), [](auto const& L, auto const& R) {
        return L.first < R.first;
    });
    
    for (auto const& elem : a) {
        std::cout << "{{";
        for (auto const& u : elem.first)
            std::cout << u << ", ";
        std::cout << "},";
        std::cout << "{";
        for (auto const& u : elem.second)
            std::cout << u << ", ";
        std::cout << "}},";
    }    
}
