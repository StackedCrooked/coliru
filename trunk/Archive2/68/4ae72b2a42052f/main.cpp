#include <iostream>
#include <string>

#define SETTER(name, type) \
void set_##name(type name) { \
    m_##name = name; \
    m_dirty = true; \
} \

class Foo {
public:
    bool isDirty() const { return m_dirty; }
    SETTER(a, int)
    SETTER(b, double)
    SETTER(c, std::string)
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
