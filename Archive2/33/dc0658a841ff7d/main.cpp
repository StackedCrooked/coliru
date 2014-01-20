#include <map>

struct S {
    S(int){}  
};

int main() {
    std::map<int, S> m{{1, S{1}}, {2, S{2}}};
    auto a = m.find(2);
}