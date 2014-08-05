#include <boost/signals2.hpp>

template<typename Result>
struct call_first
{
    typedef boost::optional<Result> result_type;

    template<typename InputIterator>
        result_type operator()(InputIterator first, InputIterator last) const
        {
            if (first != last)       
                return *first;
            else 
                return boost::none;
        }
};

#include <iostream>
#include <boost/optional/optional_io.hpp>

int foo(int i) { std::cout << "(foo)"; return i*2; }
int bar(int i) { std::cout << "(bar)"; return i+2; }

int main()
{
    using namespace boost::signals2;
    signal<int(int), call_first<int> > sig;
    std::cout << sig(42) << "\n"; // should be none ("--")

    sig.connect(foo);
    std::cout << sig(42) << "\n"; // should return 42*2

    sig.connect(bar);

    std::cout << sig(42) << "\n"; // should still return 42*2
}
