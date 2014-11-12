#include <type_traits>

struct Parent {
};

struct Child : public Parent {
};

template<class T>
struct Box {
    public:
        Box() {}
        
        template<class ChildT, typename std::enable_if<std::is_base_of<T, ChildT>::value>::type>
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