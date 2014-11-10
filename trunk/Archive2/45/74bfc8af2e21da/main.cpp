#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/functional/hash.hpp>
#include <boost/array.hpp>
#include <iostream>

namespace bmi = boost::multi_index;
namespace fw  = boost::flyweights;

struct CommonVersionKey {
    CommonVersionKey(int subdeliveryGroupId, int  retargetingId)
        : m_subdeliveryGroupId(subdeliveryGroupId), m_retargetingId(retargetingId) { }

    int  m_subdeliveryGroupId;
    int  m_retargetingId;

    bool operator==(CommonVersionKey const& o) const { return m_subdeliveryGroupId == o.m_subdeliveryGroupId && m_retargetingId == o.m_retargetingId; }
};

namespace boost {
    template <> struct hash<CommonVersionKey> {
        size_t operator()(const CommonVersionKey& ecv) const {
            size_t seed = hash_value(ecv.m_subdeliveryGroupId);
            hash_combine(seed, ecv.m_retargetingId);
            return seed;
        };
    };
}

struct ExpensiveCommonVersion : CommonVersionKey {
    ExpensiveCommonVersion(CommonVersionKey const& key) : CommonVersionKey(key) { 
        std::cout << __PRETTY_FUNCTION__ << " {" << m_subdeliveryGroupId << "," << m_retargetingId << "}\n";
    }

   ~ExpensiveCommonVersion() { 
        std::cout << __PRETTY_FUNCTION__ << " {" << m_subdeliveryGroupId << "," << m_retargetingId << "}\n";
    }

    boost::array<char, (4<<10)> m_lets_make_it_really_expensive; // :)
};

typedef boost::flyweight<fw::key_value<CommonVersionKey, ExpensiveCommonVersion>, fw::no_locking> CommonVersion;

struct VersionRecord {
    VersionRecord(int  subdeliveryGroupId, int  retargetingId, int  versionId, int  weight, int  pId, bool hdi)
        : m_common(subdeliveryGroupId, retargetingId), m_versionId(versionId),
        m_weight(weight), m_pId(pId), m_hdi(hdi)
    {
    }

    CommonVersion m_common;
    int  m_versionId;
    int  m_weight;
    int  m_pId;
    bool m_hdi;

    int subdeliveryGroupId() const { return m_common.get().m_subdeliveryGroupId; }
    int retargetingId()      const { return m_common.get().m_retargetingId;      }

    friend std::ostream& operator<<(std::ostream& os, VersionRecord const& record) {
        return os << "{ " << record.subdeliveryGroupId() << " " << record.retargetingId() << " "
            << record.m_versionId << " " << record.m_weight << " " << record.m_pId << " " << record.m_hdi << " }";
    }
};

typedef boost::multi_index_container<
    VersionRecord,
    bmi::indexed_by<
        bmi::ordered_non_unique<
            bmi::tag<struct mvKey>,
            bmi::composite_key<
                VersionRecord,
                bmi::const_mem_fun<VersionRecord,int, &VersionRecord::subdeliveryGroupId>,
                bmi::const_mem_fun<VersionRecord,int, &VersionRecord::retargetingId>
            >
        >,
        bmi::ordered_non_unique<
            bmi::tag<struct VersionId>,
            bmi::member<VersionRecord, int, &VersionRecord::m_versionId>
        >
    >
> VersionTable;

#include <boost/range/iterator_range.hpp>

int main() {

    {
        VersionTable table {
            { 21, 10,                1,  100, 123, false },
            { 21, 10,                2,  90,  123, false },
            { 21, 10,                3,  110, 123, true  },
            { 21, 10, /*version 8:*/ 8,  80,  123, true  },
            { 4,  38,                5,  101, 124, false },
            { 21, 10,                6,  91,  124, false },
            { 4,  38,                7,  111, 124, true  },
            { 4,  38, /*version 8:*/ 8,  81,  124, true  },
            { 4,  38,                9,  99,  125, false },
            { 21, 10, /*version 8:*/ 8,  89,  125, false },
            { 4,  38,                11, 109, 125, true  },
            { 4,  38, /*version 8:*/ 8,  79,  125, false },
        };
    
        // debug table output
        assert(table.size()==12);
        for (auto& record : table) std::cout << std::boolalpha << record << "\n";
    
        // so now you can do:
        auto& idx = table.get<VersionId>();
    
        std::cout << "---\nQuerying for version id 8:\n";
        for (auto& record : boost::make_iterator_range(idx.equal_range(8)))
            std::cout << record << "\n";
    }
    
    std::cout << "good bye\n";
}
