#include <boost/signals2.hpp>

int foo();

struct first_nonzero
{
    using result_type = int;

    template <typename It>
    result_type operator()(It first, It last) const
    {
    while(first != last)
    {
        if(*first != 0)
        {
            return *first;
        }
    }
    return 0;
    }
};

int foo()
{
    using signal = boost::signals2::signal<int (), first_nonzero>;
    signal s;
    return s();
}

int main()
{
    auto x = foo();
    (void)x;
}