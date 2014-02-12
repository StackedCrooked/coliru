template<typename Target, typename Value>
struct dynamic_caster {
    typedef Value                                               value_type;
    typedef Target                                              result_type;

          result_type& operator()(      value_type& v) const    {return dynamic_cast<      result_type&>(v);}
    const result_type& operator()(const value_type& v) const    {return dynamic_cast<const result_type&>(v);}
};

struct foo { virtual ~foo() {} };
struct bar : foo {};

dynamic_caster<foo, bar> x;

int main() {
    bar y;
    x(y);
}
