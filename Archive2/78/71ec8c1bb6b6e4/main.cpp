#include <iostream>
#include <string>
#include <boost/container/flat_set.hpp>

struct MyStruct {
    int id, salary;

    bool operator<(MyStruct const& other) const { return id < other.id; }
};


int main()
{
    boost::container::flat_set<MyStruct> c;
    c.reserve(10); // IMPORTANT: realloaction invalidates iterators
    auto it3 = c.emplace(MyStruct{ 3, 20  }).first;
    auto it1 = c.emplace(MyStruct{ 1, 100 }).first;
    auto it2 = c.emplace(MyStruct{ 2, 20  }).first;

    // now you can say:
    std::cout << "Index of " << (it1->id) << " is " << (it1 - c.begin()) << "\n";
    std::cout << "Index of " << (it2->id) << " is " << (it2 - c.begin()) << "\n";
    std::cout << "Index of " << (it3->id) << " is " << (it3 - c.begin()) << "\n";
}
