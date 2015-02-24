#include <functional>
#include <algorithm>
#include <iterator>


template<class it, class mather=std::plus<typename std::iterator_traits<it>::value_type> >
bool next_increasing_eq(it start, it end, typename std::iterator_traits<it>::value_type limit, mather plus={}) {
    bool n = true;
    it c = std::prev(end);
    *c = plus(*c, 1);
    if (*c == limit) {
        if (c == start)
            return false;
        n = next_increasing_eq<it>(start, c, limit);
        it prev = std::prev(c);
        *c = *prev;
    }
    return n;
}

#include <iostream>

int main() {
    char data[10] = "0000000";
    while(next_increasing_eq(data+0, data+7, '9'+1))
        std::cout << data << '\n';
}