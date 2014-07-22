#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using boost::multi_index_container;
using namespace boost::multi_index;

struct record {
    int         id;
    std::string name;
    int         age;

    friend std::ostream& operator<<(std::ostream& os,const record& e) {
        return os << e.id << " " << e.name << " " << e.age;
    }
};

typedef multi_index_container<
  record,
  indexed_by<
    ordered_unique<tag<struct id>      , BOOST_MULTI_INDEX_MEMBER(record, int        , id)>   ,
    ordered_non_unique<tag<struct name>, BOOST_MULTI_INDEX_MEMBER(record, std::string, name)> ,
    ordered_non_unique<tag<struct age> , BOOST_MULTI_INDEX_MEMBER(record, int        , age)> >
> employee_set;


employee_set get_records()
{
    employee_set es;

    es.insert(record{ 0,       "Joe",   31 });
    es.insert(record{ 1,    "Robert",   27 });
    es.insert(record{ 2,      "John",   40 });
    // next insertion will fail, as there is an record with the same ID
    es.insert(record{ 2, "Aristotle", 2387 });
    es.insert(record{ 3,    "Albert",   20 });
    es.insert(record{ 4,      "John",   57 });

    return es;
}

#include <boost/phoenix.hpp>
#include <boost/range/adaptors.hpp>
namespace phx = boost::phoenix;
using namespace phx::arg_names;
using boost::adaptors::filtered;

int main()
{
    auto const m_records = get_records();

    auto named_john = phx::bind(&record::name, arg1) == "John";

    for (auto& r : get<age>(m_records) | filtered(named_john)) {
        std::cout << r << "\n";
    };
}
