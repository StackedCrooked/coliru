#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

namespace bmi = boost::multi_index;

struct VersionRecord {
    int  m_subdeliveryGroupId;
    int  m_retargetingId;
    int  m_versionId;
    int  m_weight;
    int  m_pId;
    bool m_hdi;

    friend std::ostream& operator<<(std::ostream& os, VersionRecord const& record) {
        return os << "{ " << record.m_subdeliveryGroupId << " " << record.m_retargetingId << " "
            << record.m_versionId << " " << record.m_weight << " " << record.m_pId << " " << record.m_hdi << " }";
    }
};

typedef boost::multi_index_container<
    VersionRecord,
    bmi::indexed_by<
        bmi::ordered_unique<
            bmi::tag<struct mvKey>,
            bmi::composite_key<
                VersionRecord,
                bmi::member<VersionRecord,int, &VersionRecord::m_subdeliveryGroupId>,
                bmi::member<VersionRecord,int, &VersionRecord::m_retargetingId>
            >
        >,
        bmi::ordered_non_unique<
            bmi::tag<struct VersionId>,
            bmi::member<VersionRecord, int, &VersionRecord::m_versionId>
        >
    >
> VersionTable;

#include <iostream>
#include <boost/range/iterator_range.hpp>

int main() {

    auto table = VersionTable { 
        { 21, 10,                1,  100, 123, false },
        { 9,  27,                2,  90,  123, false },
        { 12, 25,                3,  110, 123, true  },
        { 10, 33, /*version 8:*/ 8,  80,  123, false },
        { 4,  38,                5,  101, 124, false },
        { 33, 7,                 6,  91,  124, false },
        { 34, 27,                7,  111, 124, true  },
        { 9,  11, /*version 8:*/ 8,  81,  124, false },
        { 0,  12,                9,  99,  125, false },
        { 35, 39, /*version 8:*/ 8,  89,  125, false },
        { 15, 15,                11, 109, 125, true  },
        { 25, 32, /*version 8:*/ 8,  79,  125, false },
    };

    // debug table output
    assert(table.size()==12);
    for (auto& record : table) std::cout << record << "\n";

    // so now you can do:
    auto& idx = table.get<VersionId>();

    std::cout << "---\nQuerying for version id 8:\n";
    for (auto& record : boost::make_iterator_range(idx.equal_range(8)))
        std::cout << record << "\n";
}
