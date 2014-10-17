#include <boost/range/adaptors.hpp>

template <typename TPredicate, typename TRange>
class my_filtered_range : public boost::filtered_range<TPredicate, TRange>
{
public:
    typedef boost::filtered_range<TPredicate, TRange> base_type;

    my_filtered_range(TPredicate Predicate, TRange &Range) : boost::filtered_range<TPredicate, TRange>(Predicate, Range)
    {
    }

    size_t size() const
    {
        return std::distance(this->begin(), this->end());
    }

    typename boost::range_reference<base_type>::type operator[](size_t Index)
    {
        assert(Index < this->size());
        auto It = this->begin();
        std::advance(It, Index);
        return *It;
    }
};

int main()
{

}
