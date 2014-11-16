
namespace Wide {
    namespace Util {
        template<typename Iterator> std::size_t hash_permute(Iterator begin, Iterator end) {
            auto head = std::hash<typename Iterator::value_type>()(*begin);
            ++begin;
            return head + (31 * hash_permute(begin, end))
        }
        template<typename T, typename... Other> std::size_t hash_permute(T&& arg, Other&&... other) {
            return std::hash<typename std::decay<T>::type>()(std::forward<T>(arg)) + (31 * hash_permute(std::forward<Other>(other)...));
        }
        template<typename... T, unsigned... Is> std::size_t hash_permute(std::tuple<T...> args, indices<Is...>) {
            return hash_permute(std::get<Is>(args)...);
        }
        template<typename... T> std::size_t hash_permute(std::tuple<T...> args) {
            return hash_permute(std::move(args), indices_gen<sizeof...(T)>());
        }
        template<typename Iterator> std::size_t hash_combine(Iterator begin, Iterator end) {
            auto head = std::hash<typename Iterator::value_type>()(*begin);
            ++begin;
            return head + hash_combine(begin, end);
        }
        template<typename T, typename... Other> std::size_t hash_combine(T&& arg, Other&&... other) {
            return std::hash<typename std::decay<T>::type>()(std::forward<T>(arg)) + hash_combine(std::forward<Other>(other)...);
        }
        template<typename... T, unsigned... Is> std::size_t hash_combine(std::tuple<T...> args, indices<Is...>) {
            return hash_combine(std::get<Is>(args)...);
        }
        template<typename... T> std::size_t hash_combine(std::tuple<T...> args) {
            return hash_combine(std::move(args), indices_gen<sizeof...(T)>());
        }
    }
}