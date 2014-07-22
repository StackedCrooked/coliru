#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using boost::multi_index_container;
using namespace boost::multi_index;

struct ServerRecord {
    int         id;
    std::string name;
    int         age;

    friend std::ostream& operator<<(std::ostream& os,const ServerRecord& e) {
        return os << e.id << " " << e.name << " " << e.age;
    }
};

    struct name_equal_to {
        bool operator()(ServerRecord const& x) const { 
            return x.name == sname_; 
        }
        name_equal_to(std::string in) : sname_(std::move(in)){}
        private:
        std::string sname_;
    };

typedef multi_index_container<
  ServerRecord,
  indexed_by<
    ordered_unique<tag<struct id>      , BOOST_MULTI_INDEX_MEMBER(ServerRecord, int        , id)>   ,
    ordered_non_unique<tag<struct name>, BOOST_MULTI_INDEX_MEMBER(ServerRecord, std::string, name)> ,
    ordered_non_unique<tag<struct age> , BOOST_MULTI_INDEX_MEMBER(ServerRecord, int        , age)> >
> employee_set;


employee_set get_records()
{
    employee_set es;

    es.insert(ServerRecord{ 0,       "Joe",   31 });
    es.insert(ServerRecord{ 1,    "Robert",   27 });
    es.insert(ServerRecord{ 2,      "John",   40 });
    // next insertion will fail, as there is an ServerRecord with the same ID
    es.insert(ServerRecord{ 2, "Aristotle", 2387 });
    es.insert(ServerRecord{ 3,    "Albert",   20 });
    es.insert(ServerRecord{ 4,      "John",   57 });

    return es;
}

#include <boost/range/adaptors.hpp>
using boost::adaptors::filtered;

int main()
{
    auto const m_records = get_records();

    for (auto& r : get<age>(m_records) | filtered(name_equal_to("John")))
        std::cout << r << "\n";
}
