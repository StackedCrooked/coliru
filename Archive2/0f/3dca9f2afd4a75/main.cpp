#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class parse_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

template<typename T>
bool empty(T const& range) {
    return range.empty();
}

template<typename T>
auto head(T const& range) {
    assert(!empty(range));
    return *range.begin();
}

template<typename T>
T tail(T const& range) {
    assert(!range.empty());
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

/*
auto many = [] (auto p) {
    return [=] (auto range) {
        std::vector<typename decltype(p(range))::first_type> result;
        for (;;) {
            decltype(p(range)) pair;
            try {
                pair = p(range);
            } catch (parse_error const&) {
                break;
            }
            result.push_back(pair.first);
            range = pair.second;
        }
        return std::make_pair(result, range);
    };
};
*/

auto item = [] (auto range) {
    if (empty(range)) {
        throw parse_error("expected item, got EOF");
    } else {
        return std::make_pair(head(range), tail(range));
    }
};

auto specific = [] (auto x) {
    return bind(item, [=] (auto y) {
        if (x != y) {
            throw parse_error("expected '" + std::to_string(x) + "' but got '" + std::to_string(y) + "'");
        }
        return unit(y);
    });
};

template<typename T, typename... Ts>
struct first {
    using type = T;
};

auto sequence = [] (auto... ps) {
    return [=] (auto range) {
        std::vector<typename first<typename decltype(ps(range))::first_type...>::type> result;
        auto x = { ([&] { auto pair = ps(range); result.push_back(pair.first); range = pair.second; } (), 0)... };
        (void)x;
        return std::make_pair(result, range);
    };
};

// -------------------------------------------------

#include <iostream>
#include <string>

auto sub = sequence(specific('s'), specific('u'), specific('b'));

int main() {
    try {
        {
            std::string input("subxxxxxxyyy");
            auto result = sub(input);
            for (auto x : result.first) {
                std::cout << x << '\n';
            }
            std::cout << result.second << '\n';
        }
        {
            std::string input("xxxxxxyyy");
            auto result = sub(input);
            for (auto x : result.first) {
                std::cout << x << '\n';
            }
            std::cout << result.second << '\n';
        }
    } catch (parse_error const& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
