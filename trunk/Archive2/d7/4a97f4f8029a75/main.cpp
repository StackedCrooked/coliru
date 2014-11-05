#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

template<typename It, typename OutIt>
void normalize_array(It b, It e, OutIt out) {
    using T = typename It::value_type;
    std::map<T, int> tmp;
    std::transform(b, e, std::inserter(tmp, tmp.begin()),
                   [](T v){ return std::make_pair(v, 0); });
    int i = 0;
    for (auto& ent : tmp) ent.second = i++;
    std::transform(b, e, out,
                   [&](T v){ return tmp[v]; });
}

// To get the interface expected in OP
std::vector<int> normalize_array(const std::vector<int> in) {
    std::vector<int> res;
    normalize_array(in.begin(), in.end(), std::back_inserter(res));
    return res;
}

int main(int argc, char** argv) {
    std::vector<int> in;
    for (int i = 1; i < argc; ++i)
        in.emplace_back(atoi(argv[i]));
    auto out = normalize_array(in);
    for (const auto& o : out)
        std::cout << o << ' ';
    std::cout << '\n';
    return 0;
}
