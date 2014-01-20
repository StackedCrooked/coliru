#include <algorithm>
#include <iostream>
#include <set>


template<typename It>
struct SkipIterator
{
    // TODO: accept vector<int> instead?
    SkipIterator(It it, int skip_index = -1) : it_(it), current_index_(0), skip_index_(skip_index)
    {      
        maybe_skip();
    }
    
    SkipIterator& operator++()
    {
        ++it_;
        ++current_index_;
        maybe_skip();
        return *this;
    }
    
    auto operator*() const -> decltype(*std::declval<It>())
    {
        return *it_;
    }
    
    friend bool operator!=(const SkipIterator<It>& lhs, const SkipIterator<It>& rhs)
    {
        return lhs.it_ != rhs.it_;
    }
    
private:
    void maybe_skip()
    {
        if (current_index_ == skip_index_)
        {
            ++current_index_;
            ++it_;
        }
    }
    
    It it_;
    int current_index_, skip_index_;
};


template<typename It>
struct iterator_pair
{
    auto begin() const { return b; }
    auto end() const{ return e; }
    It b, e;
};


template<typename It, typename EndIt>
auto make_range(It b, EndIt e) -> decltype(++b, b != e, iterator_pair<It>{b, e})
{
    return iterator_pair<It>{b, e};
}


template<typename Container>
auto make_range(Container&& container) -> decltype(make_range(container.begin(), container.end()))
{
    return make_range(container.begin(), container.end());
}


struct skip
{
    skip(int n) : n(n) {}
    int n;
};


template<typename Range>
auto operator|(Range&& range, skip s)
{
    using skipper = SkipIterator<decltype(begin(range))>;
    return make_range(skipper(begin(range), s.n), end(range));
}

int main()
{
    std::set<int> numbers = { 1, 2, 3, 4, 5 };

    for (auto n : make_range(numbers) | skip(0) | skip(0)) // TODO: enable skip(0, 1)
    {
        std::cout << n << ' ';
    }
}


