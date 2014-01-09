#include <iostream>
#include <numeric>
#include <array>
#include <utility>
#include <vector>


template <typename... OStreams>
class Tee {
  public:
    Tee (OStreams... ostreams) : outs({ ostreams... }) {}
    std::array<std::ostream*, sizeof...(OStreams)> outs;
};

template <typename... OStreams, typename T>
Tee<OStreams...>& operator << (Tee<OStreams...>& tee, T& t) {
    for (auto& out : tee.outs) {
        *out << t;
    }
    return tee;
}

template <typename... OStreams>
Tee<OStreams...> make_tee (OStreams... ostreams) {
    return Tee<OStreams...> (ostreams...);
}

int main () {
    auto tee = make_tee(&std::cout, &std::cout);
    tee << "test" << '\n';
}
