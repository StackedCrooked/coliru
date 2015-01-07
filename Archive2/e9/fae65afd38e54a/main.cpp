#include <type_traits>
#include <iostream>
class S{};
struct Base {
    int f53(int) { std::cout << __PRETTY_FUNCTION__ << std::endl; return 32; }
    float f54(int, float){ std::cout << __PRETTY_FUNCTION__ << std::endl; throw 0;  return 3.18; }
};

Base get_base(const S&) { return Base();}


template<typename RET, typename... Args>
struct trap_base {
    template<RET (Base::* mfptr)(Args...)>
    static RET 
    trap(S s, Args... args) {
        try {
            return (get_base(s).*mfptr)(args...);
        }
        catch (...) {
            return std::is_integral<RET>::value ? (RET)(42) : (RET)(3.14); 
        }
    }
};

struct Table {
    int (*fp_53)(S, int);
    float (*fp_54)(S, int, float);
};

struct Foo {
    Table table;
    public:
    void load53() { table.fp_53 = &trap_base<int, int>::trap<&Base::f53>; }
    void load54() { table.fp_54 = &trap_base<float, int, float>::trap<&Base::f54>; }
};

int main(){
    Foo f;
    f.load53();
    f.load54();
    std::cout << f.table.fp_53(S(), 0) << '\n';
    std::cout << f.table.fp_54(S(), 0, 1.5) << '\n';
}