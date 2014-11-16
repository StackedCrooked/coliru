namespace Wide {
    namespace Util {
        struct hash_combiner {
            std::size_t currhash = 0;
            hash_combiner operator()(std::size_t nexthash) {
                currhash ^= nexthash;
                return *this;
            }
        };
        struct hash_permuter {
            std::size_t currhash = 0;
            hash_permuter operator()(std::size_t nexthash) {
                currhash = (31 * currhash) + nexthash;
                return *this;
            }
        };
        template<typename Algorithm, typename Iterator> Algorithm hash_range(Algorithm A, Iterator begin, Iterator end) {
            A(std::hash<typename Iterator::value_type>()(*begin));
            ++begin;
            if (begin == end) return A;
            return hash(A, begin, end);
        }
        template<typename Algorithm, typename T, typename... Other> Algorithm hash(Algorithm A, T&& arg) {
            return A(std::hash<typename std::decay<T>::type>()(std::forward<T>(arg)));
        }
        template<typename Algorithm, typename T, typename... Other> Algorithm hash(Algorithm A, T&& arg, Other&&... other) {            
            return hash(A(std::hash<typename std::decay<T>::type>()(std::forward<T>(arg))), std::forward<Other>(other)...);
        }
        template<typename... T, unsigned... Is, typename Algorithm> Algorithm hash(Algorithm A, std::tuple<T...> args, indices<Is...>) {
            return hash(A, std::get<Is>(args)...);
        }
        template<typename... T, typename Algorithm> Algorithm hash(Algorithm A, std::tuple<T...> args) {
            return hash(A, std::move(args), indices_gen<sizeof...(T)>());
        }
    }
}