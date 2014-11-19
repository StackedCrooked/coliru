#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

struct info {
    int order;
    std::string name;

    friend std::istream& operator>>(std::istream& is, info& i) {
        return std::getline(is >> i.order, i.name);
    }
    friend std::ostream& operator<<(std::ostream& os, info const& i) {
        return os << i.order << " " << i.name;
    }
};

int sortinfo(info const& a, info const& b) { return a.order < b.order; }

int main() {
    std::ifstream in ("infile.txt");
    std::ofstream out("outfile.txt");

    if (in && out)
    {
        std::vector<info> inf;

        std::copy(std::istream_iterator<info>(in), {}, back_inserter(inf));
        std::sort(inf.begin(), inf.end(), sortinfo);
        std::copy(inf.begin(), inf.end(), std::ostream_iterator<info>(out, "\n"));
    } else
    {
        std::cout << "file opening failed\n";
        return 1;
    }
}
