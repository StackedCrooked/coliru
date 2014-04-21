#include <iostream>

namespace one {
namespace two {
struct g {
private:
    int x = 100;
public:
    friend int receive(const g& l) {
        return l.x;
    }
};
} // two
} // one


int main() {
    one::two::g test;
    std::cout << one::two::receive(test) << '\n';
}