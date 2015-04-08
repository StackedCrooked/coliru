#include <utility>

namespace detail {
    template<typename It, typename F>
    class filter_t {
    public:
        filter_t(It begin, It end, F predicate)
            : begin(std::move(begin))
            , end(std::move(end))
            , predicate(std::move(predicate)) { }

    private:
        It begin, end;
        F predicate;
    };
}

template<typename It, typename F>
auto filter(It begin, It end, F predicate) {
    return detail::filter_t<It, F>(std::move(begin), std::move(end), std::move(predicate));
}