#include <utility>

template<class InIt, class Num, class Pred>
std::pair<InIt, Num> accumulate_until(InIt begin, InIt end, Num n, Pred p)
{
    for(; begin != end; ++begin)
    {
        if(p(n)) break;
        n += *begin;
    }
    return std::make_pair(begin, n);
}

template<class Num>
class pred
{
    Num n;
public:
    pred(Num p = Num())
        : n(p)
    {}
    bool operator()(Num p)
    { return p > n; }
};

#include <vector>
#include <iostream>
int main()
{
    int a[] = {1, 1, 1, 42, 1, 1, 1};
    std::cout << accumulate_until(a, a+7, 0, pred<int>(42)).second << "\n";
    std::cout << accumulate_until(a, a+7, 0, std::bind2nd(std::greater<int>(), 42)).second << "\n";
}
