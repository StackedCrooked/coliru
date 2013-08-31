#include <boost/variant.hpp>


struct foo { void a() {} void b() {}  };
struct bar { void a() {} void b() {}  };


typedef boost::variant<foo, bar> Variant;

#define COMMON_METHOD(NAME) \
    struct : boost::static_visitor<> { \
        template<typename T> \
        void operator()(T & t) { \
            t.NAME(); \
        } \
    }NAME;
    
template<typename Var, typename Method>
void call(Var & var, Method & method) {
    var.apply_visitor(method);
}


COMMON_METHOD(a)
COMMON_METHOD(b)


int main()
{
    Variant var(foo{});
    var.apply_visitor(a);
    call(var, a);
}