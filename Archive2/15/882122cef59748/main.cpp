#include <algorithm>
#include <cstdio>
#include <memory>
#include <vector>

struct Object { virtual ~Object() {}; };
struct A : Object { virtual ~A() {} };
struct B : A { virtual ~B() {} };

struct registry {
    struct entry {
        const char *name;
        std::function<bool(Object*)> is_instance;
    };
    
    
    template<typename T>
    void push(const char *name) {
        T t;
        auto it = std::find_if(begin(v), end(v), [&t](const entry& e) { return e.is_instance(std::addressof(t)); });
        v.emplace(it, entry{
            name,
            [](const Object *o) { return dynamic_cast<const T*>(o) != nullptr; }
        });
    }
    
    const entry *find(Object *o) {
        auto it = std::find_if(begin(v), end(v), [o](const entry& e) { return e.is_instance(o); });
        return it == end(v) ? nullptr : &*it;
    }
    
    std::vector<entry> v;
};

int main() {
    registry rAB;
    rAB.push<A>("A");
    rAB.push<B>("B");
    for (const registry::entry& e : rAB.v) {
        std::printf("%s\n", e.name);
    }
    
    std::printf("\n");
    
    registry rBA;
    rBA.push<B>("B");
    rBA.push<A>("A");
    for (const registry::entry& e : rBA.v) {
        std::printf("%s\n", e.name);
    }
}