#include <memory>

template<class first>
first&& get_last(first&& f) {return std::forward<first>(f);}
template<class first, class...rest_ts>
auto get_last(first&&, rest_ts&&...r) ->decltype(get_last(std::forward<rest_ts>(r)...)) {return get_last(std::forward<rest_ts>(r)...);}



template<class...rest_ts, class last>
last&& get_last2(rest_ts&&..., last&& l) {return std::forward<last>(l);}




int main() {
    int t = get_last(3, 4, 5);
    int u = get_last2(3, 4, 5);
}