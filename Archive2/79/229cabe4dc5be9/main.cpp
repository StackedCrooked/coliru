#include <string>
#include <sstream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

template <typename C, typename S> C parse(S const& s) {
    istringstream ss(s); return { istream_iterator<typename C::value_type>(ss), {} };
}

int main() {
    auto L0 = parse<list<int> >("8 0 8 0 1");

    if (L0.empty())
        L0.erase(min_element(L0.begin(), L0.end()));
}
