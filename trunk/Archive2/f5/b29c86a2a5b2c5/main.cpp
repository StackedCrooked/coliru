#include <array>
#include <cstddef>

template<int... Is> struct seq {};
template<int N, int... Is> struct gen_seq : gen_seq<N-1, N-1, Is...> {};
template<int... Is> struct gen_seq<0, Is...> : seq<Is...>
{
    using type = seq<Is...>;
};

template<int N, class T = typename gen_seq<N>::type>
struct foo;

template<int N, int... Is>
struct foo<N, seq<Is...>>
{
    class float_vec
    {
    private:
      std::array<float, sizeof...(Is)> underlying_array;
    
    public:
      template<int X> using float_iden = float;
      constexpr float_vec(float_iden<Is>... pp)
        : underlying_array{{pp...}}
      {}
    };
};

int main()
{
  auto v = foo<4>::float_vec{1,2,3,4};
}