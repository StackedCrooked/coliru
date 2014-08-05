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
int main()
{
    using namespace boost::signals2;
    signal<int(int), call_first<int> > sig;
    std::cout << sig(42) << "\n"; // should be none ("--")

    sig.connect([](int i) { std::cout << "(first)";  return i*2; });
    std::cout << sig(42) << "\n"; // should return 42*2

    sig.connect([](int i) { std::cout << "(second)"; return i+2; });

    std::cout << sig(42) << "\n"; // should still return 42*2
}
