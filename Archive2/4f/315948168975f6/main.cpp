#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <iostream>

namespace bmi = boost::multi_index;

enum TimePoints { // Lets assume t1 > t2 > t3 > t4
    t1 = 100,
    t2 = 80,
    t3 = 70,
    t4 = 20,
};

using IdType = std::string;
using Symbol = std::string;
using TimeT  = unsigned int;

struct tickerUpdateInfo {
    IdType m_id;
    Symbol m_symbol;
    TimeT  m_last_update_time;

    friend std::ostream& operator<<(std::ostream& os, tickerUpdateInfo const& tui) {
        return os << "T[" << tui.m_id << ",\t" << tui.m_symbol << ",\t" << tui.m_last_update_time << "]";
    }
} static const data[] = {
    { "CBT.151.5.T.FEED", "s1", t1 },
    { "CBT.151.5.T.FEED", "s2", t2 },
    { "CBT.151.5.T.FEED", "s3", t3 },
    { "CBT.151.5.T.FEED", "s4", t4 },
    { "CBT.151.5.T.FEED", "s5", t1 },
    { "CBT.151.8.T.FEED", "s7", t1 },
    { "CBT.151.5.Q.FEED", "s8", t3 },
    // added to show freq>1 in histo
    { "CBT.151.5.T.FEED", "s2", t2 },
};

typedef bmi::multi_index_container<tickerUpdateInfo,
    bmi::indexed_by<
        bmi::ordered_non_unique<bmi::tag<struct most_active_index>,
            bmi::composite_key<tickerUpdateInfo,
                BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, TimeT,  m_last_update_time),
                BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, Symbol, m_symbol),
                BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, IdType, m_id)
        > > >
    > ticker_update_info_set;

/*
 * Now in the function get_active_ticker_count() I want to specify the key like
 *CBT.151.5.T.FEED and it should return:
 *
 *     s1       t1
 *     s2       t2
 *     s3       t3
 *     s4       t4
 *     s5       t1
 *
 * Lets assume t1 > t2 > t3 > t4, then I would like to find out such sets where
 *times are greater than t3 and also want to find the count of such symbols. How
 *do I proceed with the same, I have been able to insert but I am stuck with the
 *retrieval part. Please help!
 *
 */

#include <map>
#include <boost/range/iterator_range.hpp>

std::map<Symbol, size_t> activity_histo(ticker_update_info_set const& tuis, TimeT since)
{
    std::map<Symbol, size_t> histo;
    auto const& index = tuis.get<most_active_index>();

    auto lb = index.upper_bound(since); // for greater-than-inclusive use lower_bound
    for (auto& rec : boost::make_iterator_range(lb, index.end()))
        histo[rec.m_symbol]++;

    return histo;
}

int main()
{
    ticker_update_info_set tuis;
    tuis.insert(std::begin(data), std::end(data));

    for (auto& r : tuis) std::cout << r << "\n";

    std::cout << "\nSince t3 (" << t3 << ") there has been the following activity per symbol:\n";
    for (auto const& entry : activity_histo(tuis, t3))
        std::cout << "Symbol:" << entry.first << "\tfrequency:" << entry.second << "\n";
}
