#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>

struct MyStruct {
    int id, salary;
};

namespace bmi = boost::multi_index;
typedef boost::multi_index_container<
    MyStruct, bmi::indexed_by<
        bmi::ordered_unique<bmi::tag<struct ById>, bmi::member<MyStruct, int, &MyStruct::id>>,
        bmi::ordered_non_unique<bmi::tag<struct BySalary>, bmi::member<MyStruct, int, &MyStruct::salary>>,
        bmi::random_access<bmi::tag<struct RandomAccess> >
    > > MyStructsContainer;


int main()
{
    MyStructsContainer c;
    auto it3 = c.emplace(MyStruct{ 3, 20  }).first;
    auto it1 = c.emplace(MyStruct{ 1, 100 }).first;
    auto it2 = c.emplace(MyStruct{ 2, 20  }).first;

    auto& ra = c.get<RandomAccess>();

    // reorder RandomAccess index to match the ById
    {
        auto const& idx = c.get<ById>();
        std::vector<boost::reference_wrapper<MyStruct const> > tmp(idx.begin(), idx.end());
        ra.rearrange(tmp.begin());
    }

    // now you can say:
    std::cout << "Index of " << (it1->id) << " is " << (std::distance(ra.begin(), bmi::project<RandomAccess>(c, it1))) << "\n";
    std::cout << "Index of " << (it2->id) << " is " << (std::distance(ra.begin(), bmi::project<RandomAccess>(c, it2))) << "\n";
    std::cout << "Index of " << (it3->id) << " is " << (std::distance(ra.begin(), bmi::project<RandomAccess>(c, it3))) << "\n";
}
