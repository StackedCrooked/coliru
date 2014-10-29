#include <iostream>

template <typename T>
class weak_ref {
public:
    weak_ref(T* pointer) { _pointer = pointer; }
    ~weak_ref() { }
private:
    T* _pointer;
};

class my_class;

struct other_class {
    other_class(weak_ref<my_class> a) {}
};

struct my_class : public other_class {
    my_class() : other_class(weak_ref<my_class>(this)) {}
};

int main() {
    my_class x;   
}