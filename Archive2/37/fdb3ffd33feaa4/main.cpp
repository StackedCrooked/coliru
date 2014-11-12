#include <type_traits>

template <typename Condition, typename T = void>
using EnableIf = typename std::enable_if<Condition::value, T>::type;

struct Parent {
};

struct Child : public Parent {
};

template<class T>
struct Box {
    public:
        Box() {}
        
        template<class ChildT, EnableIf<std::is_base_of<T, ChildT>>>
        Box(const Box<ChildT>& other) {
        }
        
};

void foo(Box<Parent> test) {
}

int main() {
    Box<Parent> b;
    Box<Child> c;
    foo(b);
    foo(c);
}