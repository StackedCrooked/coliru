#include <iostream>
#include <map>

#include <boost/cstdint.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/make_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/karma.hpp>

namespace bs = boost::spirit;

struct RowData
{
    RowData() :
        field0(0),
        field1(0),
        field2(0),
        field3(0)
    {
    }

    boost::uint64_t field0;
    boost::uint64_t field1;
    boost::uint64_t field2;
    boost::uint64_t field3;
};

BOOST_FUSION_ADAPT_STRUCT(
    RowData,
    (boost::uint64_t, field0)
    (boost::uint64_t, field1)
    (boost::uint64_t, field2)
    (boost::uint64_t, field3)
)

template <typename OutputIterator>
struct RowDataGrammar :
    bs::karma::grammar< OutputIterator, std::map<boost::uint64_t, RowData>() >
{
    RowDataGrammar() : RowDataGrammar::base_type(allRowsRule)
    {
        rowDataRule =
            bs::karma::lit("(") <<
            bs::karma::ulong_ <<
            bs::karma::lit(", ") <<
            bs::karma::ulong_ <<
            bs::karma::lit(", ") <<
            bs::karma::ulong_ <<
            bs::karma::lit(", ") <<
            bs::karma::ulong_ <<
            bs::karma::lit(")");

        // I only want the value from the map. The key is dropped.
        pairRule = bs::karma::omit[bs::karma::int_] << rowDataRule;

        allRowsRule = pairRule % ", ";
    }

private:
    bs::karma::rule< OutputIterator, RowData() > rowDataRule;
    bs::karma::rule< OutputIterator, std::pair<boost::uint64_t, RowData>() > pairRule;
    bs::karma::rule< OutputIterator, std::map<boost::uint64_t, RowData>() >  allRowsRule;
};

int main(int argc, char** argv)
{
    std::map<boost::uint64_t, RowData> rowMap;

    RowData rowData;
    rowData.field0 = 0;
    rowData.field1 = 1;
    rowData.field2 = 2;
    rowData.field3 = 3;
    rowMap.insert(std::make_pair(10, rowData));

    rowData.field0 = 6;
    rowData.field1 = 7;
    rowData.field2 = 8;
    rowData.field3 = 9;
    rowMap.insert(std::make_pair(20, rowData));

    std::string generatedString;
    std::back_insert_iterator<std::string> sink(generatedString);
    RowDataGrammar< std::back_insert_iterator<std::string> > grammar;

    bs::karma::generate(sink, grammar, rowMap);

    std::cout << "output :" << generatedString << std::endl;
}
