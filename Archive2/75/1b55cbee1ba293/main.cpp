#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval_map.hpp>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/irange.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

using TimePoint = unsigned;
using DownTimes = boost::icl::interval_set<TimePoint>;
using Interval  = DownTimes::interval_type;
using Records   = std::vector<DownTimes>;

using Tally     = unsigned; // or: bit mask representing affected locations?
using DownMap   = boost::icl::interval_map<TimePoint, Tally>;

// Just for fun, removed the explicit loops from the generation too. Obviously,
// this is bit gratuitous :)
static DownTimes generate_downtime(int j) {
    return boost::accumulate(
            boost::irange(0, 5),
            DownTimes{},
            [j](DownTimes accum, int i) { return accum + Interval::closed((i*10), ((i*10) + 5 - j)); }
        );
}

int main() {
    // Initializing data for test
    using namespace boost::adaptors;
    auto const records = boost::copy_range<Records>(boost::irange(0,4) | transformed(generate_downtime));

    for (auto location : records | indexed()) {
        std::cout << "Location " << (location.index()+1) << " " << location.value() << std::endl;
    }

    // We will do a tally of affected locations per time slot
    DownMap tallied;
    for (auto& location : records)
        for (auto& incident : location)
            tallied.add({incident, 1u});

    // We will combine them so we get an interval_set defined for those periods
    // where at least 2 locations have an outage
    auto exceeds_threshold = [](DownMap::value_type const& slot) {
        return slot.second >= 2;
    };

    // just printing the union of any criticals:
    DownTimes merged;
    for (auto&& slot : tallied | filtered(exceeds_threshold) | map_keys)
        merged.insert(slot);
    
    std::cout << "Criticals: " << merged << "\n";
}
