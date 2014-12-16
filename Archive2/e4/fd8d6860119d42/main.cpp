#include <iostream>
using namespace std;

template< class... > struct voider { using type = void; };
template< class... T0toN > using void_t = typename voider<T0toN...>::type;

template <typename It, class=void>
struct dist_impl {
auto operator()(It it, It end) -> std::size_t {
    std::size_t size{};
    while (it != end) {
        ++it;
        ++size;
    }
    cout << "base distance\n";
    return size;
}
};

template<typename T>
struct is_random_access : std::is_base_of<std::random_access_iterator_tag,
    typename std::iterator_traits<T>::iterator_category> {};

template <typename It>
struct dist_impl<It, void_t<typename std::enable_if<is_random_access<It>::value>::type>> {
auto operator()(It begin, It end) -> std::size_t {
	cout << "random distance\n";
    return end - begin;
}
};

template<typename It>
auto dist(It begin, It end) -> std::size_t {
	return dist_impl<It>()(begin, end);
}

#include <vector>
#include <list>

int main() {
	vector<int> v = {1,2,3};
	list<int> l = {1,2,3};
	cout << dist(v.begin(), v.end()) <<"\n";
	cout << dist(l.begin(), l.end()) <<"\n";
	return 0;
}