#include <utility>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <iterator>

#include <deque>
#include <vector>
#include <list>
 
#include <cstdlib>
#include <cassert>

template< typename container, typename type >
std::enable_if_t< std::is_base_of< std::random_access_iterator_tag, typename std::iterator_traits< typename container::iterator >::iterator_category >::value >
replace(container & _container, typename container::value_type const & _from, type && _to)
{
    auto const beg = std::begin(_container);
    auto const end = std::end(_container);
    auto const from = std::lower_bound(beg, end, _from);
    auto const mid = std::next(from);
    if (_from < _to) {
        auto const to = std::lower_bound(from, end, _to);
        *from = std::forward< type >(_to);
        std::rotate(from, mid, to);
    } else if (_to < _from) {
        auto const to = std::lower_bound(beg, mid, _to);
        *from = std::forward< type >(_to);
        std::rotate(to, from, mid);
    } else {
        *from = std::forward< type >(_to);
    }
}

template< typename container, typename type >
std::enable_if_t< !std::is_base_of< std::random_access_iterator_tag, typename std::iterator_traits< typename container::iterator >::iterator_category >::value
                  && std::is_base_of< std::forward_iterator_tag, typename std::iterator_traits< typename container::iterator >::iterator_category >::value >
replace(container & _container, typename container::value_type const & _from, type && _to)
{
    auto const beg = std::begin(_container);
    auto const end = std::end(_container);
    if (_from < _to) {
        auto const from = std::lower_bound(beg, end, _from); 
        auto const to = std::lower_bound(std::next(from), end, _to);
        _container.insert(to, std::forward< type >(_to));
        _container.erase(from);
    } else if (_to < _from) {
        auto const to = std::upper_bound(beg, end, _to);
        auto const from = std::lower_bound(to, end, _from);
        _container.insert(to, std::forward< type >(_to));
        _container.erase(from);
    }
}

template< typename container >
bool
test(container lhs, int from, int to, container const & rhs)
{
    replace(lhs, from, to);
    return (lhs == rhs);
}

template< typename container >
bool
test()
{
    if (!test< container >({2, 4, 6, 8}, 2, 1, {1, 4, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 2, 2, {2, 4, 6, 8})) return false;//
    if (!test< container >({2, 4, 6, 8}, 2, 3, {3, 4, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 2, 5, {4, 5, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 2, 7, {4, 6, 7, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 2, 9, {4, 6, 8, 9})) return false;
    
    if (!test< container >({2, 4, 6, 8}, 4, 1, {1, 2, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 4, 3, {2, 3, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 4, 4, {2, 4, 6, 8})) return false;//
    if (!test< container >({2, 4, 6, 8}, 4, 5, {2, 5, 6, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 4, 7, {2, 6, 7, 8})) return false;
    if (!test< container >({2, 4, 6, 8}, 4, 9, {2, 6, 8, 9})) return false;
    
    if (!test< container >({2, 4, 6, 8}, 8, 1, {1, 2, 4, 6})) return false;
    if (!test< container >({2, 4, 6, 8}, 8, 3, {2, 3, 4, 6})) return false;
    if (!test< container >({2, 4, 6, 8}, 8, 5, {2, 4, 5, 6})) return false;
    if (!test< container >({2, 4, 6, 8}, 8, 7, {2, 4, 6, 7})) return false;
    if (!test< container >({2, 4, 6, 8}, 8, 8, {2, 4, 6, 8})) return false;//
    if (!test< container >({2, 4, 6, 8}, 8, 9, {2, 4, 6, 9})) return false;
    
    if (!test< container >({2}, 2, 2, {2})) return false;//
    if (!test< container >({2}, 2, 3, {3})) return false;
    if (!test< container >({2}, 2, 1, {1})) return false;
    return true;
}

int
main()
{
    assert((test< std::vector< int > >()));
    assert((test< std::deque< int > >()));
    assert((test< std::list< int > >()));
    return EXIT_SUCCESS;
}
