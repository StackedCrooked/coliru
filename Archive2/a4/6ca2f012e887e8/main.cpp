#include <iostream>   // cin/cout
#include <algorithm>  // for_each
#include <iterator>   // istream_iterator
#include <map>
#include <vector>
#include <functional> // mem_fn

using namespace std;
using Histo = map<int, size_t>;

int main() {
    Histo histo;
    std::for_each(std::istream_iterator<int>(std::cin), {}, [&](int i) { histo[i]++; });

    vector<pair<int, size_t>> v(begin(histo), end(histo));
    sort(begin(v), end(v), [](Histo::value_type a, Histo::value_type b) { return a.second > b.second; });

    for(auto& p : v)
        std::cout << p.first << " " << p.second << "\n";
}
