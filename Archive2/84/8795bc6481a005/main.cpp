#include <algorithm>
#include <iostream>
#include <set>

template<typename It>
struct SkipIterator
{
    SkipIterator(It inIt, int inSkipIndex = -1) :
        mIt(inIt),
        mCurrentIndex(0),
        mSkipIndex(inSkipIndex)
    {      
        maybe_skip();
    }
    
    SkipIterator& operator++()
    {
        ++mIt;
        ++mCurrentIndex;
        maybe_skip();
        return *this;
    }
    
    auto operator*() -> decltype(*std::declval<It>())
    {
        return *mIt;
    }
    
    
    friend bool operator!=(const SkipIterator<It>& lhs, const SkipIterator<It>& rhs)
    {
        return lhs.mIt != rhs.mIt;
    }
    
    void maybe_skip()
    {
        //std::cout << "maybe_skip: mCurrentIndex(" << mCurrentIndex << ") == mSkipIndex(" << mSkipIndex << ")?" << std::endl;
        if (mCurrentIndex == mSkipIndex)
        {
            ++mCurrentIndex;
            ++mIt;
        }
    }
    
    It mIt;
    int mCurrentIndex;
    int mSkipIndex;
};



template<typename It>
struct iterator_pair
{
    auto begin() const { return b; }
    auto begin() { return b; }
    
    auto end() const{ return e; }
    auto end() { return e; }
    It b, e;
};


template<typename It>
auto make_range(It b, It e)
{
    return iterator_pair<It>{b, e};
}

template<typename Range>
auto skip(Range range, int n)
{
    return make_range(SkipIterator<decltype(range.begin())>(range.begin(), n), SkipIterator<decltype(range.begin())>(range.end(),  -1));
}


int main()
{
    std::set<int> numbers = { 0, 1, 2 };
    
    auto range = make_range(numbers.begin(), numbers.end());

    for (auto n : skip(range, 1))
    {
        std::cout << n << ' ';
    }
    
    std::cout << std::endl;
    
}
