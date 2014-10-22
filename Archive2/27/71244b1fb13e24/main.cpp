#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>

template <typename FooType> struct Foo {
    const FooType tmp_value;

    Foo(const FooType &tmp_) : tmp_value(tmp_) {}

    template <typename Object> void operator()(Object &operand) const {
        std::cout << operand << std::endl;
        operand += tmp_value;
    }
};

template <typename BarType> struct Bar {
    const BarType tmp_value;

    Bar(const BarType &tmp_) : tmp_value(tmp_) {}

    template <typename Object> void operator()(Object &operand) const {
        std::cout << operand << std::endl;
        operand -= tmp_value;
    }
};

struct ErasedFunctor
{
    template<typename F> ErasedFunctor(F&& f) 
        : pimpl(new impl_<F>(std::forward<F>(f))) {}

    template <typename T>
    void operator()(T& oper) const {
        assert(pimpl);
        pimpl->call(oper);
    }
    
  private:
    typedef boost::variant<int32_t&, int64_t&, double&, float&> Operand;

    struct base_ { virtual void call(Operand oper) const = 0; };

    struct apply : boost::static_visitor<void> {
        template <typename F, typename T> void operator()(F const& f, T& v) const {
            std::cout << __PRETTY_FUNCTION__ << "(" << v << ")\n";
            f(v);
        }
    };

    template <typename F> struct impl_ : base_ {
        F f_;
        impl_(F&& f) : f_(std::forward<F>(f)) { }
        virtual void call(Operand oper) const override {
            boost::apply_visitor(boost::bind(apply(), boost::cref(f_), _1), oper);
        }
    };

    std::shared_ptr<base_> pimpl;
};

#include <map>
typedef std::map<std::string, ErasedFunctor> test_map;

test_map createFunMap() {
    return test_map { 
        { "foo", Foo<double>(1.0) },
        { "bar", Bar<int32_t>(1)  },
    };
}

int main() {
    test_map myMap = createFunMap();
    double t = 5.0;

    std::cout << t << std::endl;
    myMap.at("foo")(t);
    std::cout << t << std::endl;
    myMap.at("bar")(t);
    std::cout << t << std::endl;
}
