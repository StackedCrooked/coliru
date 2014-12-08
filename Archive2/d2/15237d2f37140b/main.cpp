#include <type_traits>
#include <utility>

namespace util
{

static const struct unit_t{} unit;

namespace detail
{

template<class F, class R>
struct void_converter
{
    F&& _f;

    template<class... Args>
    R operator()(Args&&... args) { return std::forward<F>(_f)(std::forward<Args>(args)...); }

    template<class... Args>
    R operator()(Args&&... args) const { return std::forward<F>(_f)(std::forward<Args>(args)...); }
};

} // detail::

template<class F, class... Args, class R = std::result_of_t<F(Args...)>,
    std::enable_if_t<!std::is_void<R>::value, int> = 0>
    decltype(auto) apply_void_to_unit(F&& f, Args&&... args)
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template<class F, class... Args, class R = std::result_of_t<F(Args...)>,
    std::enable_if_t<std::is_void<R>::value, int> = 0>
    unit_t apply_void_to_unit(F&& f, Args&&... args)
{
    std::forward<F>(f)(std::forward<Args>(args)...);
    return unit;
}

} // util::

// =========================

#include <exception>
#include <utility>
#include <boost/optional/optional.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>

namespace util
{

template<class T = unit_t, class E = std::exception_ptr>
class except
{

public:
    template<class U>
    static except<T, E> from_error(U&& error) { return except(E(std::forward<U>(error))); }

    template<class U>
    static except<T, E> from_value(U&& value) { return except(T(std::forward<U>(value))); }

    bool has_error() const { return _value.which() == 0; }
    bool has_value() const { return _value.which() == 1; }

    template<class F, class Default = unit_t>
    Default map_error(F&& f, Default&& otherwise = unit_t{}) const
    {
        using result_type = decltype(apply_void_to_unit(std::declval<F>(), std::declval<E const&>()));
        static_assert(std::is_convertible<result_type, Default>::value,
                      "except::map_error: result must be convertible to default value's type.");

        if (auto const* err = boost::get<E const>(&_value))
            return apply_void_to_unit(std::forward<F>(f), *err);
        return std::forward<Default>(otherwise);
    }

    template<class F, class Default = unit_t>
    Default map_value(F&& f, Default&& otherwise = unit_t{}) const
    {
        using result_type = decltype(apply_void_to_unit(std::declval<F>(), std::declval<T const&>()));
        static_assert(std::is_convertible<result_type, Default>::value,
                        "except::map_value: result must be convertible to default value's type.");

        if (auto const* val = boost::get<T const>(&_value))
            return apply_void_to_unit(std::forward<F>(f), *val);
        return std::forward<Default>(otherwise);
    }

private:
    template<class U>
    except(U&& v) : _value(std::forward<U>(v)) {}

    boost::variant<E, T> _value;
};

} // util::

int main()
{
    auto ex = util::except<>::from_error(nullptr);
    
    ex.map_error([](auto const&){});
    ex.map_error([](auto const&){ return 0; }, 42);
    //ex.map_error([](auto const&){}, 42);
    
    ex.map_value([](auto const&){});
    ex.map_value([](auto const&){ return 0; }, 42);
    //ex.map_value([](auto const&){}, 42);
}
