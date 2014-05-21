#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <cassert>

template<class base>
class concatenated_range_iterator 
    : public boost::iterator_facade<
        concatenated_range_iterator<base>,
        typename std::iterator_traits<base>::value_type,
        typename std::iterator_traits<base>::iterator_category,
        typename std::iterator_traits<base>::reference,
        typename std::iterator_traits<base>::difference_type
        >
{
public:
    typedef typename std::iterator_traits<base>::iterator_category iterator_category;
    typedef typename std::iterator_traits<base>::value_type        value_type;
    typedef typename std::iterator_traits<base>::difference_type   difference_type;
    typedef typename std::iterator_traits<base>::pointer           pointer;
    typedef typename std::iterator_traits<base>::reference         reference;
    
    concatenated_range_iterator() = default;
    concatenated_range_iterator(bool begin, base begin1, base end1, base begin2, base end2) 
        :current(begin?begin1:end2), end_first(end1), begin_second(begin2), in_first(begin)
        {}
        
    reference dereference() {return *current;}
    reference dereference() const {return *current;}
    bool equal(const concatenated_range_iterator& rhs) const {
        assert(end_first==rhs.end_first);
        assert(begin_second==rhs.begin_second);
        return in_first==rhs.in_first && current==rhs.current;
    }
    void increment() {
        ++current;
        if (in_first) {
            if (current==end_first) {
                current = begin_second;
                in_first = false;
            }
        } 
    }
    void decrement() {
        if (!in_first) {
            if (current==begin_second) {
                current = end_first;
                in_first = true;
            }
        }
        --current;
    }
    void advance(difference_type n) {
        if (n>=0) {
            if (in_first) {
                difference_type safe = end_first-current;
                if (safe <= n) {
                    current = begin_second;
                    n -= safe;
                    in_first = false;
                }
            }
        } else {
            if (!in_first) {
                difference_type safe = current-begin_second;
                if (safe <= n) {
                    current = end_first;
                    n += safe;
                    in_first = true;
                }
            }
        }
        current += n;
    }
    difference_type distance_to(const concatenated_range_iterator& rhs) const {
        assert(end_first==rhs.end_first);
        assert(begin_second==rhs.begin_second);
        if (in_first) {
            if (rhs.in_first) 
                return rhs.current-current;
            else
                return rhs.current-begin_second + end_first-current;
        } else {
            if (rhs.in_first) 
                return rhs.current-end_first + begin_second-current;
            else
                return rhs.current-current;
        }
    }
protected:
    base current; 
    base end_first;
    base begin_second;
    bool in_first;
};
template<class base>
std::pair<concatenated_range_iterator<base>,concatenated_range_iterator<base>>
    concatenate_ranges(base first1, base end1, base first2, base end2)
{
    return std::pair<concatenated_range_iterator<base>,concatenated_range_iterator<base>>(
        concatenated_range_iterator<base>(true, first1, end1, first2, end2),
        concatenated_range_iterator<base>(false, first1, end1, first2, end2)
        );
}


#include <vector>
#include <iostream>
int main() {
    std::vector<int> vars = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    auto range = concatenate_ranges(vars.begin(), vars.begin()+4, vars.begin()+5, vars.end());
    for(auto iter=range.first; iter!=range.second; ++iter)
        std::cout << *iter << ' ';
}