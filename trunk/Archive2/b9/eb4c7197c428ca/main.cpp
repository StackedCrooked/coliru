#include <vector>
#include <iostream>
#include <unordered_set>
#include <functional>
#include <algorithm>

struct MyClass
{
    std::string name;
    int anInt1;
    mutable bool bIsMarkedToDelete;

    bool operator==(MyClass const& o) const { return anInt1 == o.anInt1 && name == o.name; }
};

namespace std {
    template<> struct hash<MyClass> { size_t operator()(MyClass const& o) const { return o.anInt1; } };
}

int main() {
    
    std::unordered_set<MyClass> values {
        MyClass { "John", 0 }, MyClass { "Mike",  1 }, MyClass { "Dagobart", 2 },
        MyClass { "John", 3 }, MyClass { "Mike",  4 }, MyClass { "Dagobart", 5 },
        MyClass { "John", 6 }, MyClass { "Mike",  7 }, MyClass { "Dagobart", 8 },
        MyClass { "John", 9 }, MyClass { "Mike", 10 },
    }; 
    
    for(int i = 0; i<=3; ++i) {
        if(2 == i) {
            for(auto& e: values) std::cout << e.name << " "; std::cout << "\n";
            for(auto& e: values) e.bIsMarkedToDelete |= ("Mike" == e.name);

            for(auto it=begin(values); it!=end(values);) {
                if (it->bIsMarkedToDelete) it = values.erase(it);
                else ++it;
            }
        }

        std::cout << "i=" << i << ", values.size(): " << values.size() << "\n";
    }
    values.clear();
    std::cout << "Done\n";
}
