#include <map>

struct A {
    A(A& ); // <-- const missing
};

int main() {
    std::map<int, A> m;
    return m.begin() == m.end(); // line 9
}