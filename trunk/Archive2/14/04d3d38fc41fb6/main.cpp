#include <type_traits>
template <int N, typename... Args>
struct mytype {
};

using type = mytype<-1, mytype<-1, mytype<-1, int, long>>>;

template<class T, int = 0> struct assign_IDs { using type = T; };
template<class...Ts, int N, int M>
struct assign_IDs<mytype<M, Ts...>, N> { 
    using type = mytype<N, typename assign_IDs<Ts, N+1>::type...>; 
};

static_assert(std::is_same<typename assign_IDs<type>::type, mytype<0, mytype<1, mytype<2, int, long>>>>{}, "");

int main() {
}