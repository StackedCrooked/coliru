//from here
#include <vector>

class foo{
public:
         template <typename _t> int bar(const std::vector<_t> *values);

};

template <typename _t> int foo::bar(const std::vector<_t> *values) {
    return 0;
}
//to here - should be in header file to allow compiler to link it!

int main() {
   foo c;
   std::vector<int> v(5,100);
   c.bar(&v);
}