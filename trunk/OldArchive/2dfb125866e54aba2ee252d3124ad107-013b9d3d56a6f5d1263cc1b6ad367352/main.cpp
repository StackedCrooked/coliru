#include <algorithm>
#include <iostream>
#include <vector>

template <typename T, typename A>
std::ostream& operator << (std::ostream& os, const std::vector<T, A>& vec) {
    os << '{';
    for (typename std::vector<T, A>::size_type i = 0; i < vec.size(); ++i) {
        if (i)
            os << ' ';
        os << vec[i];
    }
    os << '}';
    return os;
}

template <typename T, typename A>
void do_thing(std::vector<T, A>& vec, T target, T inserted) {
    using std::swap;

    typedef typename std::vector<T, A>::size_type size_t;
    const size_t occurrences = std::count(vec.begin(), vec.end(), target);
    if (occurrences == 0) return;

    const size_t original_size = vec.size();
    vec.resize(original_size + occurrences, inserted);

    for(size_t i = original_size - 1, end = i + occurrences; i > 0; --i, --end) {
        if (vec[i] == target) {
            --end;
        }
        swap(vec[i], vec[end]);
    }
}

int main() {
    static const int values[] = { 1, 2, 3, 1, 4, 5, 1, 1, 6, 1 };
    std::vector<int> vec(values, values + sizeof(values)/sizeof(values[0]));
    std::cout << vec << '\n';
    do_thing(vec, 1, 0);
    std::cout << vec << '\n';
}
