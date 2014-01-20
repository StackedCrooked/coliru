#include <algorithm>
#include <iostream>
#include <set>

template<typename It>
struct SkipIterator
{
    SkipIterator(It inIt, int inSkipIndex) :
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
    
    
    friend bool operator==(const SkipIterator<It>& lhs, const It& rhs)
    {
        return lhs.mIt == rhs;
    }
    
    friend bool operator!=(const SkipIterator<It>& lhs, const It& rhs)
    {
        return lhs.mIt != rhs;
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
SkipIterator<It> skip(It it, int n)
{
    return SkipIterator<It>(it, n);
}



int main()
{
    std::set<int> numbers = { 0, 1, 2 };

    for (auto it = skip(numbers.begin(), 0); it != numbers.end(); ++it)
    {
        std::cout << (*it) << ' ';
    }
    
    std::cout << std::endl;
    
    for (auto it = skip(numbers.begin(), 1); it != numbers.end(); ++it)
    {
        std::cout << (*it) << ' ';
    }
    
    std::cout << std::endl;
    
    for (auto it = skip(numbers.begin(), 2); it != numbers.end(); ++it)
    {
        std::cout << (*it) << ' ';
    }
}
