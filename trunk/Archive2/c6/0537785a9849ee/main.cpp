#include <vector>

class foo{
    public:
    // ...
    template <typename _t> int bar(const std::vector<_t> *values);
    // ...
};

int main() {
    foo c;
    std::vector<int> v(5,100);
    c.bar(&v);   
}