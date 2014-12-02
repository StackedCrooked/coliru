    #include <tuple>
    
    using namespace std;
    
    template <int N>
    struct Disc {};
    
    template <typename T>
    struct pop;
    
    template <typename E, typename... Ts>
    struct pop<tuple<E, Ts...>> {
        using type = decltype(tuple_cat(declval<tuple<E>>(), declval<typename pop<tuple<Ts...>>::type>()));
    };
    
    template <typename E>
    struct pop<tuple<E>> {
        using type = tuple<>;
    };

    int main() {
    }