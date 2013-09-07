#include <boost/variant.hpp>

namespace detail
{
    template <typename R, typename Wrapped>
        struct WrapVisitor : boost::static_visitor<R>
    {
        template <typename... T> R operator()(T&&... args) const 
            noexcept(noexcept(std::declval<Wrapped>()(std::forward<T>(args)...))) 
                    { return _wrapped(std::forward<T>(args)...); }

        WrapVisitor(Wrapped&& wrapped) : _wrapped(std::move(wrapped)) {}
      private:
        Wrapped _wrapped;
    };
}

template <typename R, typename Wrapped>
detail::WrapVisitor<R, Wrapped> wrap(Wrapped&& wrapped) {
    return { std::forward<Wrapped>(wrapped) };
}

/////// demonstration

class PrivateVisistorImp : protected boost::static_visitor<double>
{
    double operator()(int i)    const { return -i;   }
    double operator()(double d) const { return d*10; }

    friend detail::WrapVisitor<double, PrivateVisistorImp>;
};

int main()
{
    using Var = boost::variant<int, double>;

    Var a = 3.14, b = 42;
    auto w = wrap<double>(PrivateVisistorImp());
    std::cout << boost::apply_visitor(w, a) << "\n";
    std::cout << boost::apply_visitor(w, b) << "\n";
}

