#include <functional>
#include <boost/optional.hpp>

template <typename T, typename Factory>
struct Lazy {
    template <typename F> Lazy(F&& f) : _factory(std::forward<F>(f)) { }

    T& get()             { return *(_value? _value : _value = _factory()); }
    T const& get() const { return *(_value? _value : _value = _factory()); }

    operator bool() const { return _value; }

  private:
    Factory _factory;
    mutable boost::optional<T> _value;
};

template <typename T, typename F>
    Lazy<T,F> make_lazy(F&& f) { return Lazy<T,F>(std::forward<F>(f)); }

#include <string>
#include <iostream>

int main() {
    auto ls = make_lazy<std::string>([] { return "Hello world"; });
    std::cout << ls.get() << "\n";
}
