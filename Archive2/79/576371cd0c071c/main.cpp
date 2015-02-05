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
    // IMPORTANT: iterators not stable (invalidated after insertion/reallocation)
    c.emplace(MyStruct{ 3, 20  });
    c.emplace(MyStruct{ 1, 100 });
    c.emplace(MyStruct{ 2, 20  });

    // now you can say:
    for (auto it = c.begin(); it != c.end(); ++it)
        std::cout << "Index of " << (it->id) << " is " << (it - c.begin()) << "\n";
}
