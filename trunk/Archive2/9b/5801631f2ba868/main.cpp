#include <map>
using namespace std;
struct A {};

map<A *, int, less<>> data;

int get_attached_value(const A *p) {
    auto i = data.find(p);
    if(i == data.end()) throw std::out_of_range("abc");
    return i->second;
}
void reset_all() {
    for (const auto &p : data) *p.first = A();
}

int main() {}