#include <set>
#include <algorithm>
#include <utility>
#include <string>
#include <iostream>

struct object {
    object(std::string name_) : name(name_), marked{false} {}
    std::string name;
    bool marked;
    
    // This would be the member table instead.
    std::set<object*> references;
};

std::set<object*> objects;

// This should be the call stack instead.
std::set<object*> roots;

template<class... Args>
object* gc_alloc(Args&&... args) {
    auto* obj = new object(std::forward<Args>(args)...);
    objects.insert(obj);
    return obj;
}

std::set<object*> visited_objects;

void mark_all(object* obj) {
    if (visited_objects.find(obj) != visited_objects.end()) return;
        
    obj->marked = true;
    visited_objects.insert(obj);
    for (auto* sub_obj : obj->references) {
        mark_all(sub_obj);
    }
}

void unmark_all(object* obj) {
    if (visited_objects.find(obj) != visited_objects.end()) return;
        
    obj->marked = false;
    visited_objects.insert(obj);
    for (auto* sub_obj : obj->references) {
        unmark_all(sub_obj);
    }
}

void gc_collect() {
    std::for_each(roots.begin(), roots.end(), &mark_all);
    visited_objects.clear();
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (!(*it)->marked) {
            delete *it;
            objects.erase(it);
        }
    }
    std::for_each(roots.begin(), roots.end(), &unmark_all);
    visited_objects.clear();
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
    gc_collect();
    gc_collect();
    
    auto* obj9 = gc_alloc("obj9");
    roots.insert(obj9);
    
    // Cycle test!
    auto* obj10 = gc_alloc("obj10");
    obj9->references.insert(obj10);
    obj10->references.insert(obj9);
    
    // More complex cycles!
    auto* obj11 = gc_alloc("obj11");
    roots.insert(obj11);
    auto* obj12 = gc_alloc("obj12");
    auto* obj13 = gc_alloc("obj13");
    auto* obj14 = gc_alloc("obj14");
    auto* obj15 = gc_alloc("obj15");
    auto* obj16 = gc_alloc("obj16");
    for (auto* obj : {obj11, obj12, obj13, obj14, obj15, obj16}) {
        for (auto* objj : {obj11, obj12, obj13, obj14, obj15, obj16}) {
            obj->references.insert(objj);
        }
    }
    
    gc_collect();
    gc_collect();
    gc_collect();
    gc_collect();
    
    for (auto* obj : objects) {
        std::cout << obj->name << '\n';
    }
}
