#include <type_traits>
template <int N, typename... Args>
struct mytype {
};

using type = mytype<-1, mytype<-1, mytype<-1, int, long>, mytype<-1, char, double>>, mytype<-1, mytype<-1, int, long>, mytype<-1, char, double>>>;

template<class T, int N = 0, class = mytype<-1>> struct assign_IDs {
    using type = T; 
    static constexpr int next_index = N;
};

template<class T, class...Ts, int N, int M1, int M2>
struct assign_IDs<mytype<M1, T, Ts...>, N, mytype<M2>> {
    using T_assigned = assign_IDs<T, N + 1>;
    using next = assign_IDs<mytype<N, Ts...>, T_assigned::next_index, mytype<N, typename T_assigned::type>>;
    using type = typename next::type;
    static constexpr int next_index = next::next_index;
};

template<class T, class...Ts, class... Vs,  int N, int M1, int M2>
struct assign_IDs<mytype<M1, T, Ts...>, N, mytype<M2, Vs...>> {
    using T_assigned = assign_IDs<T, N>;
    using next = assign_IDs<mytype<M1, Ts...>, T_assigned::next_index, mytype<M2, Vs..., typename T_assigned::type>>;
    using type = typename next::type;
    static constexpr int next_index = next::next_index;
};

template<class... Vs, int N, int M1, int M2>
struct assign_IDs<mytype<M1>, N, mytype<M2, Vs...>> {
    using type = mytype<M2, Vs...>;
    static constexpr int next_index = N;
};

static_assert(std::is_same<typename assign_IDs<type>::type, mytype<0, mytype<1, mytype<2, int, long>, mytype<3, char, double>>, mytype<4, mytype<5, int, long>, mytype<6, char, double>>>>{}, "");

int main() {
}