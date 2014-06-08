#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using boost::multi_index_container;
using namespace boost::multi_index;

struct employee {
    int         id;
    std::string name;
    int         age;
};

typedef multi_index_container<
  employee,
  indexed_by<
    ordered_unique<tag<struct id>      , BOOST_MULTI_INDEX_MEMBER(employee, int        , id)>   ,
    ordered_non_unique<tag<struct name>, BOOST_MULTI_INDEX_MEMBER(employee, std::string, name)> ,
    ordered_non_unique<tag<struct age> , BOOST_MULTI_INDEX_MEMBER(employee, int        , age)> >
> employee_set;

int main()
{
    employee_set es;
    struct {} _ = get<age>(es);
}
