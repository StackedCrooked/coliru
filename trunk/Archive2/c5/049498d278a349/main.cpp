#include <iostream>
#include <map>
#include <iterator>

template <typename Iter>
struct map_iterator : public std::iterator<std::bidirectional_iterator_tag,
                      typename Iter::value_type::second_type> 
{
    map_iterator() {}
    map_iterator(Iter j) : i(j) {}
    map_iterator& operator++() { ++i; return *this; }
    map_iterator& operator--() { --i; return *this; }
    bool operator==(map_iterator j) const { return i == j.i; }
    bool operator!=(map_iterator j) const { return !(*this == j); }
    typename map_iterator::reference operator*() { return i->second; }
    typename map_iterator::pointer operator->() { return &i->second; }
    map_iterator operator--(int) {
        auto tmp = *this; --(*this);
        return tmp;
    }
    map_iterator operator++(int) {
        auto tmp = *this; ++(*this);
        return tmp;
    }
protected:
    Iter i;
};
template <typename Iter>
inline map_iterator<Iter> make_map_iterator(Iter j) {
    return map_iterator<Iter>(j);
}

int main()
{
    std::map<int,std::string> m {{1, "Hi"},{2, "Bye"}};

    for (auto i = make_map_iterator(m.begin()); i != make_map_iterator(m.end()); i++)
    {
        std::cout << *i << std::endl;
    }
}