#include <tuple>

template<int, int> struct ix{};
template<typename...> struct seq{ using type = seq; };
template<typename Acc, int I, int J, int... Sizes>
struct gen_seq { using type = Acc; };
template<typename... Acc, int I, int J, int... Sizes>
struct gen_seq<seq<Acc...>, I, J, 0, Sizes...> : gen_seq<seq<Acc...>, I+1, 0, Sizes...> {};
template<typename... Acc, int I, int J, int N, int... Sizes>
struct gen_seq<seq<Acc...>, I, J, N, Sizes...> : gen_seq<seq<Acc..., ix<I, J>>, I, J+1, N-1, Sizes...> {};

int main() {
    struct {}_ = gen_seq<seq<>, 0, 0, 3, 2>::type();
}