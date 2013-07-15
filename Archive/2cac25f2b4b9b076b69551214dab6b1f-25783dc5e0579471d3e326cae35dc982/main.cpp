template <typename T, typename Iter, int Skip>
class SkipIterator
{
public:
    SkipIterator(Iter baseIter) :
        baseIter_(baseIter)
    {
    }

    void operator++()
    {
        baseIter_ += Skip;
    }

    T &operator*()
    {
        return *baseIter_;
    }

private:
    Iter baseIter_;
};

#include <iterator>

template <int Skip, typename Iter>
auto make_skip_iterator(Iter it)
{
    return SkipIterator<
        typename std::iterator_traits<Iter>::value_type, Iter, Skip
        >(it);
}

#include <vector>
#include <iostream>

int main()
{
    std::vector<double> dataFromSomewhere{1, 2, 3, 4, 5, 6};
    auto skipper = make_skip_iterator<3>(dataFromSomewhere.begin());
    
    std::cout << *skipper << std::endl;
    ++skipper;
    std::cout << *skipper;
}