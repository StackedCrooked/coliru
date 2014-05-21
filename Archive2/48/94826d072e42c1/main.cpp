#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <cassert>
#include <array>

template<class first>
first&& get_last(first&& f) {return std::forward<first>(f);}
template<class first, class...rest_ts>
auto get_last(first&&, rest_ts&&...r) ->decltype(get_last(std::forward<rest_ts>(r)...)) {return get_last(std::forward<rest_ts>(r)...);}

template<class base, int num_ranges>
class concatenated_range_iterator 
    : public boost::iterator_facade<
        concatenated_range_iterator<base,num_ranges>,
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
    
    template<class...rest_ts>
    concatenated_range_iterator(bool begin, base first, rest_ts... rest) 
        :current(begin?first:get_last(rest...)), ranges{{first, rest...}},range_index(begin?1:num_ranges*2-1)
        {static_assert(sizeof...(rest)==num_ranges*2-1, "incorrect number of range iterator pairs passed");}
        
    reference dereference() {return *current;}
    reference dereference() const {return *current;}
    bool equal(const concatenated_range_iterator& rhs) const {
        assert(ranges==rhs.ranges);
        return range_index==rhs.range_index && current==rhs.current;
    }
    void increment() {
        ++current;
        if (current==ranges[range_index]) {
            assert(range_index<num_ranges*2+1);
            range_index+=2;
            current = ranges[range_index-1];
        } 
    }
    void decrement() {
        if (current==ranges[range_index-1]) {
            assert(range_index>1);
            range_index-=2;
            current = ranges[range_index+1];
        }
        --current;
    }
    void advance(difference_type n) {
        difference_type safe = ranges[range_index] - current;
        while(safe <= n) {
            n -= safe;
            range_index += 2;
            current = ranges[range_index-1];
            safe = ranges[range_index]-current;
        }
        current += n;
    }
    difference_type distance_to(const concatenated_range_iterator& rhs) const {
        assert(ranges==rhs.ranges);
        if (range_index>rhs.range_index) 
            return -rhs.distance_to(*this);
            
        difference_type dist = 0;
        base current = this->current;
        int range_index = this->range_index;
        while(range_index != rhs.range_index) {
            dist += ranges[range_index] - current;
            assert(range_index<num_ranges*2-1);
            current = ranges[range_index+1];
            range_index += 2;
        }
        dist += rhs.current - current;
        return dist;
    }
protected:
    base current; 
    std::array<base,num_ranges*2> ranges;
    int range_index;
};

template<class base, class...rest_ts>
std::pair<concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>,concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>>
    concatenate_ranges(base first, rest_ts...rest)
{
    return std::pair<concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>,concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>>(
        concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>(true, first, rest...),
        concatenated_range_iterator<base,sizeof...(rest_ts)/2+1>(false, first, rest...)
        );
}


#include <vector>
#include <iostream>
int main() {
    std::vector<int> vars0 = {0, 1, 2, 3};
    std::vector<int> vars1 = {4, 5, 6};
    std::vector<int> vars2 = {7, 8, 9, 10, 11};
    
    auto range = concatenate_ranges(vars0.begin(), vars0.end(), vars1.begin(), vars1.end(), vars2.begin(), vars2.end());
    for(auto iter=range.first; iter!=range.second; ++iter)
        std::cout << *iter << ' ';
}