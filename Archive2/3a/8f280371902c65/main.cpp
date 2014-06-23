#include <stdio.h>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

//while (pBeg != pEnd)
//{
//    if (pred(*pBeg))
//    {
//        return *pBeg;
//    }
//
//    pBeg += inc;
//}

enum SearchType { gt, ge, le, lt, eq };
enum SearchResult { Exact, Less, Greater, None };

template <SearchResult Sr, bool HasEq>
struct SearchResultAdjuster;

template <SearchResult Sr>
struct SearchResultAdjuster<Sr, false>
{
    SearchResult operator()(const int /*key*/, const int /*found*/)
    {
        return Sr;
    }
};

template <SearchResult Sr>
struct SearchResultAdjuster<Sr, true>
{
    SearchResult operator()(const int key, const int found)
    {
        return key == found ? Exact : Sr;
    }
};

template <>
struct SearchResultAdjuster<Exact, false>
{
    SearchResult operator()(const int /*key*/, const int /*found*/)
    {
        return Exact;
    }
};

template<SearchType St>
struct SearchOps;

template<>
struct SearchOps<gt>
{
    typedef greater<const int> Pred;
    typedef SearchResultAdjuster<Greater, false> Adjust;
};

template<>
struct SearchOps<ge>
{
    typedef greater_equal<const int> Pred;
    typedef SearchResultAdjuster<Greater, true> Adjust;
};

template<>
struct SearchOps<lt>
{
    typedef less<const int> Pred;
    typedef SearchResultAdjuster<Less, false> Adjust;
};

template<>
struct SearchOps<le>
{
    typedef less_equal<const int> Pred;
    typedef SearchResultAdjuster<Less, true> Adjust;
};

template<>
struct SearchOps<eq>
{
    typedef equal_to<const int> Pred;
    typedef SearchResultAdjuster<Exact, false> Adjust;
};

template <SearchType St, typename It>
SearchResult myFind(
    It first,
    typename iterator_traits<It>::difference_type length,
    typename iterator_traits<It>::value_type key,
    typename remove_const<typename iterator_traits<It>::value_type>::type & found)
{
    auto last = first + length;
    auto foundIt = find_if(first, last, [=](typename iterator_traits<It>::value_type a){ return typename SearchOps<St>::Pred()(a, key); });

    if (foundIt == last)
    {
        return None;
    }

    found = *foundIt;
    return typename SearchOps<St>::Adjust()(key, found);
}

void print(SearchResult result, int found)
{
    cout << result << ": " << found << endl;
}

int main()
{
    const int arr[] = { 1, 3, 5, 7, 9 };
    const int arr_len = 5;

    SearchResult result;
    int found;

    //My_Find_if(iterator<const int*>(arr), iterator<const int*>(arr + _countof(arr)), [=](int a){ return a >= n; }, found);

    result = myFind<ge>(arr, arr_len, 6, found);
    print(result, found);

    result = myFind<ge>(arr, arr_len, 5, found);
    print(result, found);

    result = myFind<le>(reverse_iterator<const int*>(arr + arr_len), arr_len, 6, found);
    print(result, found);

    //cout << myFind(arr, arr + _countof(arr), [=](int a){ return a >= n; }, found) << ": " << found << endl;
    //cout << myFind(reverse_iterator<const int*>(arr + _countof(arr)), reverse_iterator<const int*>(arr), [=](int a){ return a <= n; }, found) << found << endl;
    //return myFind<1>(arr, arr + _countof(arr), [=](int a){ return a >= n; });

    return 0;
}
