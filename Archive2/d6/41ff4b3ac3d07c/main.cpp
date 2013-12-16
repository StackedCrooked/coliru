#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include <map>

std::ostream& operator<<(std::ostream& o, const std::pair<int, int>& p) {
    o << p.first << p.second;
    return o;
}

struct PAIR : std::pair<int, int>
{
    using std::pair<int, int>::pair;
};

int main(int argc, char* argv[]) {
std::vector<std::pair<int, int> > data;
data.push_back(std::pair<int, int>(50, 42));
std::copy(data.begin(), data.end(), std::ostream_iterator<PAIR>(std::cout, "\n"));
    return 0;
}