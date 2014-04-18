#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
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
        bmi::random_access<>
    > >;

static std::ostream& operator<<(std::ostream& os, Table const& table) {
    for(auto const& element : table) 
        os << element << "; ";
    return os;
}

int main()
{
    Table table {
        { 42, "aap" },
        { 43, "noot" },
        { 44, "mies" } 
    };

    std::cout << "Before: " << table << "\n";

    table.modify(table.begin(),  [](Data& v) { v.i *= v.i; });
    std::cout << "Edit 1: " << table << "\n";

    table.modify(table.begin()+2, [](Data& v) { v.index1 = "touched"; });
    std::cout << "Edit 2: " << table << "\n";
}
