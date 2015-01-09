#include <functional>
#include <boost/optional.hpp>

template <typename T>
struct Lazy {
    template <typename... Args> Lazy(Args const&... args) 
        : _factory([=] { return T(args...); })
    { }

    T& get()             { return *(_value? _value : _value = _factory()); }
    T const& get() const { return *(_value? _value : _value = _factory()); }

    explicit operator bool() const { return _value; }

  private:
    std::function<T()> _factory;
    mutable boost::optional<T> _value;
};

#include <string>
#include <iostream>

int main() {
    Lazy<std::string> ls("Hello world");
    std::cout << ls.get() << "\n";

    // Lazy<std::string> oops(42.7, true); // no matching function call
}
