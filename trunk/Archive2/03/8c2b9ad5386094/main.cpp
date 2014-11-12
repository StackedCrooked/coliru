#include <iostream>
#include <string>

#define SETTER(name) \
template <typename T> \
void set_##name(T name) { \
    m_##name = name; \
    m_dirty = true; \
} \

class Foo {
public:
    bool isDirty() const { return m_dirty; }
    SETTER(a)
    SETTER(b)
    SETTER(c)
private:
    int m_a;
    double m_b;
    std::string m_c;
    bool m_dirty;
};

int main() {
    Foo f;
    std::cout << f.isDirty();
    f.set_b(4.5);
    std::cout << f.isDirty();
}
