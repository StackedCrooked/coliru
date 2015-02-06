#include <iostream>
#include <boost/algorithm/string/join.hpp>
#include <boost/unordered_set.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
/*
template<typename C1, typename C2>
void castContainer(const C1& source, C2& destination)
{
    typedef typename C1::value_type source_type;
    typedef typename C2::value_type destination_type;
    destination.resize(source.size());
    std::transform(source.begin(), source.end(), destination.begin(), boost::lexical_cast<destination_type, source_type>);
}
*/
class A
{
    public:
    static const uint_fast32_t                          kRestrictedNZValues[];
    static const boost::unordered_set<uint_fast32_t>    kRestrictedNZValuesSet;
    //static const std::vector<std::string>               kRestrictedNZValuesStringVector;
    static const std::string                            kDetermineLowestUnusedNZQuery;
    
    //template<typename C>
    static std::vector<std::string> transformToString(const uint_fast32_t iValues[]);
};

std::vector<std::string> A::transformToString(const uint_fast32_t iValues[])
{
    std::vector<std::string> aVector;
    std::cout << "SIZE: " << sizeof(iValues) << std::endl;
    for(uint_fast32_t i = 0 ; i < sizeof(iValues) ; ++i)
    {
        std::cout << "value " << i << ": " << iValues[i] << std::endl;
        aVector.push_back(boost::lexical_cast<std::string>(iValues[i]));
    }
    //castContainer(iValues, aVector);
    return aVector;
}




const uint_fast32_t A::kRestrictedNZValues[] = {16, 17, 18, 19};
const boost::unordered_set<uint_fast32_t> A::kRestrictedNZValuesSet(
    A::kRestrictedNZValues,
    A::kRestrictedNZValues + sizeof(A::kRestrictedNZValues)/sizeof(A::kRestrictedNZValues[0])
);
//const std::vector<std::string> kRestrictedNZValuesStringVector = A::transformToString(A::kRestrictedNZValues);

const std::string A::kDetermineLowestUnusedNZQuery =
    std::string(
    "SELECT missing_sequence_value FROM ( "
        "SELECT "
            "seq.val AS missing_sequence_value "
        "FROM ( "
            "SELECT "
                "level - 1 AS val "
            "FROM dual "
            "CONNECT BY LEVEL <= (SELECT MAX(ord) FROM CRB_APT_TABLE) "
        ") seq "
        "LEFT JOIN CRB_APT_TABLE t "
            "ON seq.val = t.ord "
        "WHERE t.ord IS NULL "
            "AND seq.val NOT IN ("
    )
    + std::string(boost::algorithm::join(A::transformToString(A::kRestrictedNZValues), ", "))
    + std::string(") "
        "ORDER BY "
            "missing_sequence_value "
    ") WHERE rownum = 1");

int main() {
    // your code goes here
    std::cout << "sizeof(A::kRestrictedNZValues): "sizeof(A::kRestrictedNZValues) << std::endl
        << "sizeof(A::kRestrictedNZValues[0]): " << sizeof(A::kRestrictedNZValues[0]) << std::endl
        << "sizeof(A::kRestrictedNZValues)/sizeof(A::kRestrictedNZValues[0]): " << sizeof(A::kRestrictedNZValues)/sizeof(A::kRestrictedNZValues[0]) << std::endl;
    std::cout << A::kDetermineLowestUnusedNZQuery;
	return 0;
}
