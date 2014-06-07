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

    friend std::ostream& operator<<(std::ostream& os,const employee& e) {
        return os << e.id << " " << e.name << " " << e.age << std::endl;
    }
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

    es.insert(employee{ 0,       "Joe",   31 });
    es.insert(employee{ 1,    "Robert",   27 });
    es.insert(employee{ 2,      "John",   40 });
    // next insertion will fail, as there is an employee with the same ID
    es.insert(employee{ 2, "Aristotle", 2387 });
    es.insert(employee{ 3,    "Albert",   20 });
    es.insert(employee{ 4,      "John",   57 });

    auto const& by_age = get<age>(es);
    auto upper = by_age.upper_bound(32);

    for (auto& e : boost::make_iterator_range(by_age.begin(), upper))
        std::cout << e.name << " is " << e.age << " years old\n";
}
