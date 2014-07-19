#include <iostream>
#include <functional>
#include <cassert>
#include <string>

template <typename T>
void expect(T what, std::function<T()> from) {
    assert(from() == what);
}

constexpr int gimme_5() {
    return 5;
}

class Guy {
public:
    Guy(std::string const & name) :
        m_name(name) {}
        
    std::string name() const {
        return m_name;
    }
private:
    std::string m_name;
};

int main() {
    expect<int>(2, [] { return 2; });
    expect<int>(5, gimme_5);
    Guy guy("Peter");
    expect<std::string>("Peter", std::bind(&Guy::name, &guy));
}
