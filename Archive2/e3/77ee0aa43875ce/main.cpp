#include <boost/optional.hpp>
#include <deque>
#include <iostream>
#include <utility>

template<typename T>
class stream {
public:
    template<typename F>
    explicit stream(F generator)
        : generator(std::move(generator)) { }

    T const& operator[](std::size_t index) const {
        return at(index);
    }

    T const& at(std::size_t index) const {
        while (cache.size() <= index) {
            if (!more()) {
                break;
            }
        }

        return cache.at(index);
    }

private:
    bool more() const {
        auto item = generator();
        if (item) {
            cache.push_back(std::move(*item));
            return true;
        } else {
            return false;
        }
    }

    mutable std::deque<T> cache;
    std::function<boost::optional<T>()> generator;
};

int main() {
    int a = 0, b = 1;
    stream<int> my_stream([=] () mutable -> boost::optional<int> {
        auto result = b;
        auto c = a + b;
        if (result > 1000) {
            return boost::none;
        } else {
            a = b;
            b = c;
            return result;
        }
    });

    for (std::size_t i = 0; true; ++i) {
        std::cout << my_stream.at(i) << '\n';
    }
}
