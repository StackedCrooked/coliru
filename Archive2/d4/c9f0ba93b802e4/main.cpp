#include <iostream>   // cin/cout
#include <algorithm>  // for_each
#include <iterator>   // istream_iterator
#include <map>
#include <list>
#include <functional> // reference_wrapper

using namespace std;
using Histo = map<int, size_t>;

int main() {
    Histo histo;
    list<std::reference_wrapper<Histo::value_type>> order;

    std::for_each(std::istream_iterator<int>(std::cin), {}, [&](int i)
        {
            auto insertion = histo.insert({i, size_t(0)});

            if (insertion.second)
                order.emplace_back(*insertion.first);

            insertion.first->second++;
        });

    for(auto& p : order)
        std::cout << p.get().first << " " << p.get().second << "\n";
}
