#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

struct employee {
    employee(int id, const std::string& name) : id(id), name(name) {}

    // natural ordering for set
    bool operator<(const employee& e) const { return id<e.id; }

    int         id;
    std::string name;

    inline friend std::ostream& operator << (
        std::ostream& os, const employee& rEmp) {
        os << "id=" << rEmp.id << ", name=" << rEmp.name << std::endl;
        return os;
    }
};

// TYPEDEFS
// define a multiply indexed set with indices by id and name
// @TODO Use the multi_index_container to replace the 
// guts of the IndexContainer shown below
typedef boost::multi_index_container<
    employee,
    boost::multi_index::indexed_by<
        // sort by employee::operator<
        boost::multi_index::ordered_unique<boost::multi_index::identity<employee>>,
        // sort by less<string> on name
        boost::multi_index::ordered_non_unique<boost::multi_index::member<employee, std::string, &employee::name> >
    >
> employee_set;

int main() {
    // this is the sort of behavior I need where I can specify multiple indexes
    employee_set employees;
    employees.insert(employee(1, "John"));
    employees.insert(employee(2, "Paul"));
    employees.insert(employee(3, "John"));
    // get a view to index #0 (id) - unique
    std::copy(employees.cbegin(), employees.cend(),
        std::ostream_iterator<employee>(std::cout));
    // get a view to index #1 (name)
    const employee_set::nth_index<1>::type& name_index = employees.get<1>();
    std::copy(name_index.begin(), name_index.end(), std::ostream_iterator<employee>(std::cout));    
}
