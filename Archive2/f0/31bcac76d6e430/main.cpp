#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <random>

template<class Iter, class Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
unsigned int merge(Iter begin, Iter mid, Iter end, const Cmp& cmp = Cmp())
{
    auto lhs_len = std::distance(begin,mid);
    unsigned int count = 0;
    
    // reserve space for sort-bed
    std::vector<typename std::iterator_traits<Iter>::value_type> sorted;
    
    Iter lhs = begin, rhs = mid;
    while (lhs != mid && rhs != end)
    {
        if (cmp(*lhs,*rhs) || !cmp(*rhs,*lhs))
            sorted.emplace_back(*lhs++);
        else
        {   // bump count with rhs moves
            sorted.emplace_back(*rhs++);
            count += (lhs_len - std::distance(begin,lhs));
        }
    }
    
    // finish missing segment
    while (lhs != mid)
        sorted.emplace_back(*lhs++);
    while (rhs != end)
        sorted.emplace_back(*rhs++);

    // move sorted data back into place
    std::copy(sorted.begin(), sorted.end(), begin);
    
    return count;
}

// mergesort algorithm
template<class Iter, class Cmp = std::less<typename std::iterator_traits<Iter>::value_type>>
unsigned int mergesort(Iter begin, Iter end, const Cmp& cmp = Cmp())
{
    auto len = std::distance(begin, end);
    if (len < 2)
        return 0;
    
    Iter mid = std::next(begin, len/2);
    
    return mergesort(begin, mid, cmp) +
           mergesort(mid, end, cmp) +
           merge(begin, mid, end, cmp);
}

// simple sequence printer
template< typename T, template<class,class...> class V, class... Args>
std::ostream& operator <<(std::ostream& os, const V<T,Args...>& seq)
{
    for (auto const& x : seq)
        os << x << ' ';
    return os;
}

int main()
{
    // used for sample vector creation
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<> dist(1,99);
    
    for (unsigned int i=5; i<=25; ++i)
    {
        // populat some random data
        std::vector<int> data;
        data.reserve(i);
        
        // generate sample data
        std::generate_n(std::back_inserter(data), data.capacity(), [&](){ return dist(rng);});
        std::cout << data << '\n';
        
        unsigned int inv = mergesort(data.begin(), data.end());
        std::cout << data << ": " << inv << "\n\n";
    }
    return 0;
}