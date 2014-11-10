#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

namespace bmi = boost::multi_index;

struct VersionData {
    int     m_versionId;
    int     m_weight;
    int     m_pId;
    bool    m_hdi;
};

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

int main() {

    auto data = mvDataContainer { 
        VersionsData { 1, 2, VersionDataContainer { 
                 VersionData {  1, 100, 123, false   },
                 VersionData {  2,  90, 123, false   },
                 VersionData {  3, 110, 123,  true   },
                 VersionData {  4,  80, 123, false   },
            }   },
        VersionsData {  1, 3, VersionDataContainer       {
                 VersionData {  5, 101, 124, false   },
                 VersionData {  6,  91, 124, false   },
                 VersionData {  7, 111, 124,  true   },
                 VersionData {  8,  81, 124, false   },
            }   },
        VersionsData {  2, 4, VersionDataContainer       {
                 VersionData {  9,  99, 125, false   },
                 VersionData { 10,  89, 125, false   },
                 VersionData { 11, 109, 125,  true   },
                 VersionData { 12,  79, 125, false   },
            } },
    };

}
