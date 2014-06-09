#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

template <class Iterator>
class SimpleIterator {
    Iterator iter;

  public:
    SimpleIterator(Iterator iter) : iter(iter) {}

    typename std::iterator_traits<Iterator>::value_type &operator*() const {
        return *iter;
    }

    typename std::iterator_traits<Iterator>::value_type *operator->() const {
        return &(*iter);
    }

    SimpleIterator &operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(const SimpleIterator &other) const {
        return iter != other.iter;
    }
};

template <class Iterator>
SimpleIterator<Iterator> make_iter(Iterator iter) {
    return SimpleIterator<Iterator>(iter);
}

int main() {
    using namespace std;
    vector<int> vec = {3,2,1,4,5,23,1,2,3,4,436,4,4,1};

    {
        // Simple for-loop will work
        auto first = make_iter(begin(vec));
        auto last = make_iter(end(vec));
        cout << "for-loop\n";
        for (; first != last; ++first) {
            cout << *first << ", ";
        }
        cout << "\n\n";
    }

    {
        // STL algorithm usage won't compile.
        auto first = make_iter(begin(vec));
        auto last = make_iter(end(vec));
        first = find(first, last, 23);
        if (first != last) {
            cout << "23 inside vector.\n";
        }
    }
}