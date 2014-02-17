#include <cstring>

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>



template <typename Object, typename Visitor>
class TargettedVisitor {
public:
    TargettedVisitor() {
        RegistrationVisitor registrer(map);
        Object::Apply(registrer);
        std::sort(map.begin(), map.end(), NameSorter);
    } // TargettedVisitor

    bool apply(char const* name, Visitor& visitor) const {
        // 1. Find Element
        Element const key{name, nullptr};
        typename Map::const_iterator const it = std::lower_bound(map.begin(), map.end(), key, NameSorter);
        
        if (it == map.end()) { return false; }
        
        // Here, we know that *it >= key, if key < *it they are not equal
        if (NameSorter(key, *it)) { return false; }
        
        FuncPtr const func = it->second;
        func(name, visitor);
        return true;
    }
    
private:
    using FuncPtr = void (*)(char const*, Visitor&);
    using Element = std::pair<char const*, FuncPtr>;
    using Map = std::array<Element, Object::Count>;
    
    static bool NameSorter(Element const& left, Element const& right) { return strcmp(left.first, right.first) < 0; }
    
    template <typename T, T Object::* Ptr, size_t Index>
    static void Visit(char const* name, Visitor& visitor) {
        visitor.template visit<T, Ptr, Index, Object::Count>(name);
    } // Visit

    struct RegistrationVisitor {
        explicit RegistrationVisitor(Map& m): map(m) {}

        template <typename T, T Object::* Ptr, size_t Index, size_t>
        void visit(char const* name) {
            FuncPtr const func = &Visit<T, Ptr, Index>;
            map[Index] = std::make_pair(name, func);
        }

        Map& map;
    }; // struct RegistrationVisitor

    Map map;
}; // class TargettedVisitor

struct Visitable {
    static size_t const Count = 2;
    
    template <typename Visitor>
    static void Apply(Visitor& visitor) {
        visitor.template visit<int, &Visitable::hello, 0, Count>("hello");
        visitor.template visit<std::string, &Visitable::world, 1, Count>("world");
    } // Apply
    
    template <typename Visitor>
    static bool Apply(char const* name, Visitor& visitor) {
        static TargettedVisitor<Visitable, Visitor> const Targetter = {};
        return Targetter.apply(name, visitor);
    } // Apply
    
    int hello = 42;
    std::string world = "World!";
}; // struct Visitable


template <typename Object>
struct Printer {
    explicit Printer(Object const& o): object(o) {}
    
    template <typename T, T Object::* Ptr, size_t Index, size_t Count>
    void visit(char const* name) const {
        std::cout << (Index+1) << "/" << Count << ": '" << name << "' = '" << (object.*Ptr) << "'\n";
    }
    
    Object const& object;
}; // struct Printer


int main() {
    Visitable v;
    
    {
        Printer<Visitable> const printer(v);
        Visitable::Apply(printer);
    }
    
    {
        Printer<Visitable> const printer(v);
        Visitable::Apply("hello", printer);
        Visitable::Apply("foo", printer);
    }

    return 0;
}