#include <iostream>
#include <string>

class Foo {
public:
    bool isDirty() const { return m_dirty; }
    void set_a(int a) {
        m_a = a;
        m_dirty = true;
    }
    void set_b(double b) {
        m_b = b;
        m_dirty = true;
    }
    void set_c(std::string c) {
        m_c = c;
        m_dirty = true;
    }
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
