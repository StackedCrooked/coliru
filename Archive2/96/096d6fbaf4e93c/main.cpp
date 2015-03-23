#include <iostream>
#include <vector>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>

namespace bmi = boost::multi_index;

struct MyClass
{
    std::string name;
    int         anInt1;

    MyClass(std::string name, int i) : name(name), anInt1(i) {}

    //bool operator==(MyClass const& o) const { return boost::tie(name, anInt1) == boost::tie(o.name, o.anInt1); }
    //bool operator< (MyClass const& o) const { return boost::tie(name, anInt1) <  boost::tie(o.name, o.anInt1); }

    friend std::ostream& operator << (std::ostream& out, const MyClass& ac) {
        return out << ac.name << " " << ac.anInt1;
    }
};

using Table = bmi::multi_index_container<MyClass,
      bmi::indexed_by<
        bmi::random_access<bmi::tag<struct as_vector> >,
        bmi::ordered_non_unique<bmi::tag<struct by_number>,
            bmi::member<MyClass, int, &MyClass::anInt1>
        >,
        bmi::hashed_non_unique<bmi::tag<struct by_name>,
            bmi::member<MyClass, std::string, &MyClass::name>
        >
      >
    >;

void alternative_remove_mikes(Table& values);

int main()
{
    Table values {
        { "John",     0 },
        { "Mike",     0 },
        { "Dagobart", 25 },
        { "John",     5 },
        { "Mike",     25 },
        { "Dagobart", 26 },
        { "John",     10 },
        { "Mike",     25 },
        { "Dagobart", 27 },
        { "John",     15 },
        { "Mike",     27 },
    };

    auto& name_idx = values.get<by_name>();

    std::cout << "\nBEFORE: Ordered by number:\n";
    for(auto& e: values.get<by_number>()) 
        std::cout << e << "\n";

    std::cout << "\nBEFORE: O(1) lookup by name:\n";
    for(auto& e : boost::make_iterator_range(name_idx.equal_range("Mike")))
        std::cout << e << '\n';

    std::cout << "removing all Mikes\n";
    name_idx.erase("Mike");
    // alternative_remove_mikes(values);

    std::cout << "\nAFTER: Ordered by number:\n";
    for(auto& e: values.get<by_number>()) 
        std::cout << e << "\n";

    std::cout << "\nAFTER: O(1) lookup by name:\n";
    for(auto& e : boost::make_iterator_range(name_idx.equal_range("Mike")))
        std::cout << e << '\n';

    values.clear();

    std::cout << "Done\n----------------------------\n";
}

void alternative_remove_mikes(Table& values) {
    // this uses the same `remove_if` approach together with the `rearrange()` feature of `random_access` index
    std::vector<boost::reference_wrapper<MyClass const> > refs(values.begin(), values.end());

    // remove_if is not good enough since it will leave the removed end unspecified
    auto it = std::partition(refs.begin(), refs.end(), [](MyClass const& mc) { return "Mike" != mc.get().name; });

    std::cout << "Removing " << std::distance(it, refs.end()) << " items:\n";

    values.rearrange(refs.begin());

    auto newend = values.begin() + std::distance(refs.begin(), it);
    for (auto& e : boost::make_iterator_range(newend, values.end()))
        std::cout << " -- removing " << e << "\n";

    values.erase(newend, values.end());
}
