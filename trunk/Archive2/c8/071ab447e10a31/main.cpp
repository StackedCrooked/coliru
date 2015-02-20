#include <tuple>
#include <type_traits>
#include <list>
#include <iostream>
#include <typeinfo>

template<std::size_t Max_N, typename List>
class list_to_tuple {
public:
    using value_type = typename List::value_type;
    using iterator_type = typename List::const_iterator;
    using tuple_type = decltype(std::tuple_cat(
        std::tuple<typename List::value_type>(),
        typename list_to_tuple<Max_N-1, List>::tuple_type()
    ));

    tuple_type operator()(const List& lst, const value_type& sentinel) {
        return convert(lst.begin(), lst.end(), sentinel);
    }

    tuple_type convert(iterator_type begin, iterator_type end, const value_type& sentinel) const {
        list_to_tuple<Max_N-1, List> remaining;
        if(begin != end) {
            auto current = std::make_tuple(*begin);
            ++begin;
            return std::tuple_cat(current, remaining.convert(begin, end, sentinel));
        } else {
            return std::tuple_cat(std::make_tuple(sentinel), remaining.convert(begin, end, sentinel));
        }
    }
};

template<typename List>
class list_to_tuple<0, List> {
public:
    using value_type = typename List::value_type;
    using iterator_type = typename List::const_iterator;
    using tuple_type = std::tuple<>;

    tuple_type convert(iterator_type begin, iterator_type end, const value_type& sentinel) const {
        return std::tuple<>();
    }
};

int main() {
    std::list<int> lst = {1, 2, 3};
    list_to_tuple<5, std::list<int>> to_tup;
    auto tup = to_tup(lst, 0);
	std::cout << std::get<0>(tup) << std::endl;
	std::cout << std::get<1>(tup) << std::endl;
	std::cout << std::get<2>(tup) << std::endl;
	std::cout << std::get<3>(tup) << std::endl;
	std::cout << std::get<4>(tup) << std::endl;
	std::cout << typeid(tup).name() << std::endl;
}