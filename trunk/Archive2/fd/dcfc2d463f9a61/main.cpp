#include <type_traits>
#include <initializer_list>


constexpr
bool are_all_true(bool v)
{
    return v;
}

template<typename... Vs>
constexpr
bool are_all_true(bool head, Vs... vs)
{
    return head && are_all_true(vs...);
}


struct base {
    virtual void foo() { }
};


void foo_everything(std::initializer_list<base *> list){
    for(auto i : list) i->foo();
}

template<typename... Ts,
        typename = typename std::enable_if< are_all_true(std::is_base_of<base, typename std::decay<Ts>::type>::value...) , int>::type
        >
void foo_everything(Ts&&... args) {
    foo_everything({&args...});
}



struct derived1 : base {
    void foo() override { }
};

struct derived2 : base {
    void foo() override { }
};



int main()
{
    derived1 a;
    derived2 b;
    foo_everything(a, b);
}