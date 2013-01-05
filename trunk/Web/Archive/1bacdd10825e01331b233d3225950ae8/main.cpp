#include <unordered_set>
#include <algorithm>
#include <utility>
#include <string>
#include <iostream>

struct object {
    object(std::string name_) : name(name_), marked{false} {}
    std::string name;
    bool marked;
    
    // This would be the member table instead.
    std::unordered_set<object*> references;
};

std::unordered_set<object*> objects;

// This should be the call stack instead.
std::unordered_set<object*> roots;

template<class... Args>
object* gc_alloc(Args&&... args) {
    auto* obj = new object(std::forward<Args>(args)...);
    objects.insert(obj);
    return obj;
}

void mark_all(object* obj) {
    obj->marked = true;
    std::for_each(obj->references.begin(), obj->references.end(), &mark_all);
}

void gc_collect() {
    std::for_each(roots.begin(), roots.end(), &mark_all);
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (!(*it)->marked) {
            delete *it;
            objects.erase(it);
        }
    }
}

int main() {
    auto* obj1 = gc_alloc("obj1");
    roots.insert(obj1);
    
    auto* obj2 = gc_alloc("obj2");
    roots.insert(obj2);
    
    auto* obj3 = gc_alloc("obj3");
    obj2->references.insert(obj3);
    
    gc_alloc("obj4");
    gc_alloc("obj5");
    gc_alloc("obj6");
    gc_alloc("obj7");
    gc_alloc("obj8");
    
    gc_collect();
    
    for (auto* obj : objects) {
        std::cout << obj->name << '\n';
    }
}
