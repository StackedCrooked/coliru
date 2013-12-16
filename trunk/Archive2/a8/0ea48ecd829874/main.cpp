#include <vector>
#include <iostream>
#include <utility>

template <class TIterator>
struct Range
{
 Range(const TIterator &begin, const TIterator &end)
     :_begin(begin), _end(end) {}

 TIterator begin() { return _begin; }
 TIterator end() { return _end; }

private:
 TIterator _begin;
 TIterator _end;
};

template <class TRange>
auto make_range(TRange r) -> Range<decltype(std::begin(r))>
{
    return { std::begin(r), std::end(r) };   
}

template <class TRange>
auto make_range2(TRange &r) -> Range<decltype(std::begin(r))>
{
    return { std::begin(r), std::end(r) };   
}


int main()
{
    std::vector<int> vec = {1,2,3,4,5};
    auto r = make_range(vec);
    
    for (auto i : r)
    {
        std::cout << i << std::endl;   
    }
    
    std::vector<int> vec2 = {1,2,3,4,5};
    auto r2 = make_range2(vec2);
    
    for (auto i : r2)
    {
        std::cout << i << std::endl;   
    }
    
    return 0;
}
