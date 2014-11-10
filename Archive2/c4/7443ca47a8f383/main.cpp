#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

// for intrusive multiset
#include <boost/intrusive/set.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

namespace bmi = boost::multi_index;
namespace bi  = boost::intrusive;

struct VersionData : bi::set_base_hook<bi::link_mode<bi::auto_unlink> > {
    VersionData(int versionId, int weight=0, int pId=0, bool hdi=false) : 
        m_versionId(versionId), m_weight(weight), m_pId(pId), m_hdi(hdi) { }

    int     m_versionId;
    int     m_weight;
    int     m_pId;
    bool    m_hdi;

    friend std::ostream& operator<<(std::ostream& os, VersionData const& vd) {
        return os << "{ " << vd.m_versionId << " " << vd.m_weight << " " << vd.m_pId << " " << vd.m_hdi << " }";
    }

    struct ById {
        bool operator()(VersionData const& a, VersionData const& b) const  { return a.m_versionId < b.m_versionId; }
    };
};

typedef bi::set<VersionData, bi::constant_time_size<false>, bi::compare<VersionData::ById> > VersionIndex;

typedef boost::multi_index_container<
    VersionData,
    bmi::indexed_by<
        bmi::ordered_non_unique<
            bmi::tag<struct VersionId>,
            bmi::member<VersionData, int, &VersionData::m_versionId>
        >
    >
> VersionDataContainer;

struct VersionsData
{
    int m_subdeliveryGroupId;
    int m_retargetingId;

    VersionDataContainer m_versionData;
};

typedef boost::multi_index_container<
    VersionsData,
    bmi::indexed_by<
    bmi::ordered_unique<
            bmi::tag<struct mvKey>,
            bmi::composite_key<
                VersionsData,
                bmi::member<VersionsData,int, &VersionsData::m_subdeliveryGroupId>,
                bmi::member<VersionsData,int, &VersionsData::m_retargetingId>
            >
        >
    >
> mvDataContainer;

void insert(
        mvDataContainer& into, VersionIndex& global_version_index,
        int subdeliveryGroupId, int retargetingId, int
        versionId, int weight, int pId, bool hdi) 
{
    auto& mainIdx = into.get<mvKey>();
    auto insertion = mainIdx.insert(VersionsData { subdeliveryGroupId, retargetingId, VersionDataContainer {} });
    mainIdx.modify(insertion.first, [&](VersionsData& record) {
            auto insertion = record.m_versionData.insert(VersionData { versionId, weight, pId, hdi });
            global_version_index.insert_equal(const_cast<VersionData&>(*insertion.first));
    });
}

int main() {

    VersionIndex global_version_index;
    mvDataContainer table;

    insert(table, global_version_index, 21, 10,                1,  100, 123, false);
    insert(table, global_version_index, 9,  27,                2,  90,  123, false);
    insert(table, global_version_index, 12, 25,                3,  110, 123, true);
    insert(table, global_version_index, 10, 33, /*version 8:*/ 8,  80,  123, false);
    insert(table, global_version_index, 4,  38,                5,  101, 124, false);
    insert(table, global_version_index, 33, 7,                 6,  91,  124, false);
    insert(table, global_version_index, 34, 27,                7,  111, 124, true);
    insert(table, global_version_index, 9,  11, /*version 8:*/ 8,  81,  124, false);
    insert(table, global_version_index, 0,  12,                9,  99,  125, false);
    insert(table, global_version_index, 35, 39, /*version 8:*/ 8,  89,  125, false);
    insert(table, global_version_index, 15, 15,                11, 109, 125, true);
    insert(table, global_version_index, 25, 32, /*version 8:*/ 8,  79,  125, false);

    // debug table output
    assert(table.size()==12);

    // so now you can do:
    std::cout << "---\nQuerying for version id 8:\n";
    for (auto& record : boost::make_iterator_range(global_version_index.equal_range(8)))
        std::cout << record << "\n";

    table.erase(table.find(boost::make_tuple(10,33))); // auto unlinks from global_version_index

    std::cout << "---\nQuerying for version id 8:\n";
    for (auto& record : boost::make_iterator_range(global_version_index.equal_range(8)))
    {
        std::cout << "TEST\n";
        //std::cout << record << "\n";
    }
}
