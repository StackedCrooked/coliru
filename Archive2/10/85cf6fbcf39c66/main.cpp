#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <set>


template<typename It>
struct range
{
    auto begin() const { return b; }
    auto end() const { return e; }
    
    friend It begin(const range<It>& r) { return r.begin(); }        
    friend It end(const range<It>& r) { return r.end(); }
    
    It b, e;
};


template<typename It>
auto make_range(It b, It e)
{
    return range<It>{b, e};
}


template<typename Container>
auto make_range(Container&& c)
{
    return make_range(begin(c), end(c));
}


namespace detail {


template<typename It, int N>
struct SkipIterator
{
    // end iterator
    SkipIterator(It it) : cur_it_(it), end_it_(it), cur_idx_(0), skip_list_()
    {    
    }
    
    // begin iterator, end iterator, array or skipped indices
    SkipIterator(It it, It end, int (&indices)[N]) : cur_it_(it), end_it_(end), cur_idx_(0), skip_list_()
    {    
        auto b = indices;
        auto e = b + N;
        std::copy(b, e, &skip_list_[0]);
        maybe_skip();
    }
    
    SkipIterator& operator++()
    {
        ++cur_it_;
        ++cur_idx_;
        maybe_skip();
        return *this;
    }
    
    auto operator*() const -> decltype(*std::declval<It>())
    {
        return *cur_it_;
    }
    
    friend bool operator!=(const SkipIterator<It, N>& lhs, const SkipIterator<It, N>& rhs)
    {
        return lhs.cur_it_ != rhs.cur_it_;
    }
    
private:
    void maybe_skip()
    {
        auto b = &skip_list_[0];
        auto e = b + N;
        while (cur_it_ != end_it_ && std::find(b, e, cur_idx_) != e)
        {
            ++cur_idx_;
            ++cur_it_;
        }
    }
    
    It cur_it_;
    It end_it_;
    int cur_idx_;
    int skip_list_[N];
};


template<int Count>
struct skip_t
{
    template<typename ...idx>
    skip_t(idx ...n) : n_{ n... } { }    
    
    int n_[Count];
};


template<typename Range, int Count>
auto operator|(Range&& range, skip_t<Count> s)
{
    using std::begin; using std::end;
    using skipper = detail::SkipIterator<decltype(begin(range)), Count>;
    return make_range(skipper(begin(range), end(range), s.n_), skipper(end(range)));
}


template<typename ...idx>
auto skip(int head, idx ...tail)
{
    return detail::skip_t<1 + sizeof...(idx)>(head, tail...);
};


} // namespace detail


using detail::skip;


int main()
{   
    // test with contiguous storage
    for (auto n : "012345" | skip(0, 1, 4, 5))
    {
        std::cout << n;
    }
    std::cout << std::endl;
    
    // test with non-contiguous storage
    std::set<int> numbers = { 0, 1, 2, 3, 4, 5 };
    for (auto n : make_range(numbers) | skip(0, 1, 4, 5))
    {
        std::cout << n;
    }
    std::cout << std::endl;
}


