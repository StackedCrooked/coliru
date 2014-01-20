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


template<typename Container>
auto make_range(Container&& container) -> decltype(make_range(container.begin(), container.end()))
{
    return make_range(container.begin(), container.end());
}


struct skip_
{
    int n;
};


skip_ skip(int n)
{
    return {n};
}

template<typename Range>
auto operator|(Range&& range, skip_ s)
{
    return make_range(SkipIterator<decltype(range.begin())>(range.begin(), s.n), SkipIterator<decltype(range.begin())>(range.end(),  -1));
}


int main()
{
    std::set<int> numbers = { 0, 1, 2 };
    
    for (auto n : make_range(numbers))
    {
        std::cout << n << ' ';
    }
        
     std::cout << std::endl;

    for (auto n : make_range(numbers) | skip(0))
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;
    


    for (auto n : make_range(numbers) | skip(0) | skip(0))
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;
    


    for (auto n : make_range(numbers) | skip(0) | skip(0) | skip(0))
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

}
