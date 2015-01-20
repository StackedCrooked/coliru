#include <algorithm>
#include <cstdio>
#include <memory>
#include <utility>
#include <vector>

struct Object { virtual ~Object() {}; };
struct A : Object { virtual ~A() {} };
struct B : A { virtual ~B() {} };

struct registry {
    struct entry {
        const char *name;
        bool(*is_instance)(const Object*);
        void (*throws)();
        bool (*catches)(void(*)());
    };
    
    static bool is_base_of(const entry& base, const entry& derived) {
        return base.catches(derived.throws);
    }
    
    template<typename T>
    void push(const char *name) {
        entry e = {
            name,
            [](const Object *o) { return dynamic_cast<const T*>(o) != nullptr; },
            [] { throw static_cast<T*>(nullptr); },
            [](void (*throws)()) { try { throws(); } catch (T*) { return true; } catch (...) {} return false; }
        };
        auto it = std::find_if(begin(v), end(v), [&e](const entry& base) { return is_base_of(base, e); });
        v.emplace(it, std::move(e));
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