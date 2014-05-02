#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

template <typename Container, typename F, int RA = 0, int ONU = 1>
    F stabled_ordered(Container const& container, F&& f)
{
    using RAIt  = typename Container::template nth_index<RA> ::type::const_iterator;
    using ONUIt = typename Container::template nth_index<ONU>::type::const_iterator;
    auto& ordered = container.template get<ONU>();

    std::vector<RAIt> v(ordered.size());
    auto output = v.begin();

    for(ONUIt cursor = ordered.begin(); cursor != ordered.end(); )
    {
        // get range with equiv. keys
        auto key_range = ordered.equal_range(ordered.key_extractor()(*cursor));
        cursor = key_range.second;

        // project into first index
        auto saved = output;

        for(auto it = key_range.first; it != key_range.second; ++it)
            *output++ = boost::multi_index::project<RA>(container, it);

        // put into original order
        std::sort(saved, output);

        for_each(saved, output, [&f](RAIt const& it) { f(*it); });
    }

    return std::forward<F>(f);
}
    
#include <iostream>
#include <vector>

using namespace boost::multi_index;
using namespace std;

struct Entry {
    int nonUniqueInt;
    string somethingExtra;
};

using Container_t = multi_index_container<Entry, indexed_by<
    random_access<>,
    ordered_non_unique<
        // ***** What can I put here? *****
        member<Entry, int, &Entry::nonUniqueInt>
    >
>>;

std::vector<Entry> const sampleData{
    {1, "first"}, {2, "second"}, {3, "third"}, {3, "fourth"}, {2, "fifth"}, {1, "sixth"}
};

// fillFront should make the sequence LIFO
template <typename T>
void fillFront(T & container) {
    for (auto & item : sampleData) {
        container.push_front(item);
    }
}

// fillBack should make the sequence FIFO
template <typename T>
void fillBack(T & container) {
    for (auto & item : sampleData) {
        container.push_back(item);
    }
}

int main() {
    Container_t container;
    auto & sequenced = container.get<0>();

    fillFront(sequenced);

    stabled_ordered(container, [](Entry const& entry) {
            cout << entry.nonUniqueInt << ": " << entry.somethingExtra << endl;
        });

    cout << endl;
    container.clear();

    fillBack(sequenced);
    stabled_ordered(container, [](Entry const& entry) {
            cout << entry.nonUniqueInt << ": " << entry.somethingExtra << endl;
        });
}
