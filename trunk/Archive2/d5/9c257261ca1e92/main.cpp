#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

struct info {
    int order;
    std::string name;

    bool operator<(info const& o) const { return order < o.order; }
};

static inline std::istream& operator>>(std::istream& is, info& i) {
    return std::getline(is >> i.order, i.name);
}
static inline std::ostream& operator<<(std::ostream& os, info const& i) {
    return os << i.order << " " << i.name;
}

int main() {
    std::ifstream in ("infile.txt");
    std::ofstream out("outfile.txt");

    if (!in || !out) {
        std::cout << "file opening failed\n";
        return 1;
    }

    std::vector<info> inf;

    std::copy(std::istream_iterator<info>(in), {}, back_inserter(inf));
    std::sort(inf.begin(), inf.end());
    std::copy(inf.begin(), inf.end(), std::ostream_iterator<info>(out, "\n"));
}
