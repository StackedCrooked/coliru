#include <stdexcept>
#include <utility>

class parse_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

template<typename T>
bool empty(T const& range) {
    return range.empty();
}

template<typename T>
T tail(T const& range) {
    auto begin = range.begin();
    ++begin;
    return T(begin, range.end());
}

auto unit = [] (auto x) {
    return [=] (auto range) {
        return std::make_pair(x, range);
    };
};

auto bind = [] (auto p, auto f) {
    return [=] (auto range) {
        auto pair = p(range);
        return f(pair.first)(pair.second);
    };
};

auto item = [] (auto range) {
    if (empty(range)) {
        throw parse_error("expected item, got EOF");
    } else {
        return std::make_pair(head(range), tail(range));
    }
};

int main() {
    return 0;
}
