#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>


template<typename It, int N>
struct SkipIterator
{
    SkipIterator(It it, int* indices) : it_(it), current_index_(0), skip_indices_(), is_end_(indices == nullptr)
    {      
        if (indices)
        {
            auto b = indices;
            auto e = b + N;
            std::copy(b, e, &skip_indices_[0]);
            maybe_skip();
        }
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
    
    friend bool operator!=(const SkipIterator<It, N>& lhs, const SkipIterator<It, N>& rhs)
    {
        return lhs.it_ != rhs.it_;
    }
    
private:
    void maybe_skip()
    {
        assert(!is_end_);
        auto b = &skip_indices_[0];
        auto e = b + N;
        if (std::find(b, e, current_index_) != e)
        {
            ++current_index_;
            ++it_;
        }
    }
    
    It it_;
    int current_index_;
    int skip_indices_[N];
    bool is_end_;
};


template<typename It>
struct iterator_pair
{
    auto begin() const { return b; }
    auto end() const { return e; }
    
    friend It begin(const iterator_pair<It>& range)
    {
        return range.begin();
    }
    
    friend It end(const iterator_pair<It>& range)
    {
        return range.end();
    }
    
    It b;
    It e;
};


template<typename It>
auto make_range(It b, It e) -> decltype(iterator_pair<It>{b, e})
{
    return iterator_pair<It>{b, e};
}


template<typename Container>
auto make_range_c(Container&& container) -> decltype(make_range(container.begin(), container.end()))
{
    return make_range(container.begin(), container.end());
}


template<int Count>
struct skip_t
{
    template<typename ...Index>
    skip_t(Index ...n) : n_{ n... }
    {
    }
    
    int n_[Count];
};


template<typename ...Index>
auto skip(int head, Index ...tail) -> skip_t<1 + sizeof...(Index)>
{
    return skip_t<1 + sizeof...(Index)>(head, tail...);
};


template<typename Range, int Count>
auto operator|(Range&& range, skip_t<Count> s)
{
    using std::begin;
    using std::end;
    using skipper = SkipIterator<decltype(begin(range)), Count>;
    auto b = skipper(begin(range), s.n_);
    auto e = skipper(end(range), nullptr);
    return make_range(b, e);
}


#include <thread>
#include <unistd.h>


int main()
{
    std::thread([=]{ usleep(1000); assert(!"timeout"); }).detach();
    
    std::set<int> numbers = { 0, 1, 2, 3, 4, 5 };
    
    auto range = make_range_c(numbers);
    
    auto range_with_skips = range | skip(0, 2, 4);

    for (auto n : range_with_skips)
    {
        std::cout << n << ' ';
    }
}


