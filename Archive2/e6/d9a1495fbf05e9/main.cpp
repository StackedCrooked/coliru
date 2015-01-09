#include <functional>
#include <boost/variant.hpp>

template <typename T>
struct Lazy {
    template <typename... Args> Lazy(Args const&... args) 
        : _storage(Factory([=] { return T(args...); }))
    { }

    T& get()             { return ensure(); }
    T const& get() const { return ensure(); }

    explicit operator bool() const { return _storage.which(); }

  private:
    using Factory = std::function<T()>;
    mutable boost::variant<Factory, T> _storage;

    T& ensure() const {
        if (!_storage.which())
            _storage = boost::get<Factory>(_storage)();

        return boost::get<T>(_storage);
    }
};

#include <string>
#include <iostream>

int main() {
    Lazy<std::string> ls("Hello world");
    std::cout << ls.get() << "\n";

    // Lazy<std::string> oops(42.7, true); // no matching function call
}
