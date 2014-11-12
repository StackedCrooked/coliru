#include <vector>
#include <iostream>
#include <vector>
#include <boost/intrusive/unordered_set.hpp>

namespace bic = boost::intrusive;

struct MyClass : bic::unordered_set_base_hook<bic::link_mode<bic::auto_unlink>>
{
    std::string name;
    int anInt1;
    mutable bool bIsMarkedToDelete;

    MyClass(std::string name, int i) : name(name), anInt1(i), bIsMarkedToDelete(false) {}

    bool operator==(MyClass const& o) const { return anInt1 == o.anInt1 && name == o.name; }

    struct hasher { size_t operator()(MyClass const& o) const { return o.anInt1; } };
};

typedef bic::unordered_set<MyClass, bic::hash<MyClass::hasher>, bic::constant_time_size<false> > HashTable;

int main() {
    
    std::vector<MyClass> values {
        MyClass { "John", 0 }, MyClass { "Mike",  1 }, MyClass { "Dagobart", 2 },
        MyClass { "John", 3 }, MyClass { "Mike",  4 }, MyClass { "Dagobart", 5 },
        MyClass { "John", 6 }, MyClass { "Mike",  7 }, MyClass { "Dagobart", 8 },
        MyClass { "John", 9 }, MyClass { "Mike", 10 },
    }; 
    
    HashTable::bucket_type buckets[100];
    HashTable hashtable(values.begin(), values.end(), HashTable::bucket_traits(buckets, 100)); 

    for(int i = 0; i<=3; ++i) {
        if(2 == i) {
            for(auto& e: values) std::cout << e.name << " "; std::cout << "\n";
            for(auto& e: values) e.bIsMarkedToDelete |= ("Mike" == e.name);

            values.erase(std::remove_if(begin(values), end(values), std::mem_fn(&MyClass::bIsMarkedToDelete)));
        }

        std::cout << "i=" << i << ", values.size():    " << values.size()    << "\n";
        std::cout << "i=" << i << ", hashtable.size(): " << hashtable.size() << "\n";
    }
    values.clear();
    std::cout << "Done\n";
}
