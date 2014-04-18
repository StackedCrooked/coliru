#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <iostream>

struct Data
{
    int i;
    std::string index1;

    friend std::ostream& operator<<(std::ostream& os, Data const& v) {
        return os << "{ " << v.i << ", '" << v.index1 << "' }";
    }

};

namespace bmi = boost::multi_index;

using Table = bmi::multi_index_container<
    Data,
    bmi::indexed_by<
        bmi::random_access<>,
        bmi::ordered_unique<bmi::member<Data, std::string, &Data::index1> >
    > >;

static std::ostream& operator<<(std::ostream& os, Table const& table) {
    os << "insertion order:  "; for(auto const& element : table) os << element << "; ";
    os << "\nsecondary index: ";for(auto const& element : table.get<1>()) os << element << "; ";
    return os << "\n";
}

int main()
{
    Table table {
        { 42, "aap" },
        { 43, "noot" },
        { 44, "mies" } 
    };

    std::cout << "Before:\n" << table << "\n";

    table.modify(table.begin(),  [](Data& v) { v.i *= v.i; });
    std::cout << "Edit 1:\n" << table << "\n";

    table.modify(table.begin()+2, [](Data& v) { v.index1 = "touched"; });
    std::cout << "Edit 2:\n" << table << "\n";

    table.replace(table.begin(),  { 42, "aap" });
    std::cout << "Replace 1:\n" << table << "\n";

    table.replace(table.begin()+2,  { 4444, "MIES" });
    std::cout << "Replace 1:\n" << table << "\n";

}
